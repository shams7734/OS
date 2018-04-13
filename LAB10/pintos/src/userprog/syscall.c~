#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include <user/syscall.h>
#include "devices/input.h"
#include "devices/shutdown.h"
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "threads/interrupt.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#include "userprog/process.h"

struct lock filesys_lock;

struct process_file {
  struct file *file;
  int fd;
  struct list_elem elem;
};

int process_add_file (struct file *f);
struct file* process_get_file (int fd);
void get_args(struct intr_frame *f,int *args,int n);

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  lock_init(&filesys_lock);
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void halt()
{
	printf("System is shutting down due to halt system call!!\n");
	shutdown_power_off();
}

void exit(int status)
{
	struct thread *cur = thread_current();
	if (thread_alive(cur->parent))
	{
	  cur->cp->status = status;
	}
	printf("Exited from %s process due to exit system call with status %d!!\n",cur->name,status);
	thread_exit();
}


pid_t exec (const char *cmd_line)
{
	pid_t pid = process_execute(cmd_line);
	struct child_process* cp = get_child_process(pid);
	while (cp->load == NOT_LOADED)
	{
	  barrier();
	}
	if (cp->load == LOAD_FAIL)
	{
	  return ERROR;
	}
	return pid;
}

int wait (pid_t pid)
{
	return process_wait(pid);
}

bool create (const char *file, unsigned initial_size)
{
  lock_acquire(&filesys_lock);
  bool success = filesys_create(file, initial_size);
  lock_release(&filesys_lock);
  return success;
}

bool remove (const char *file)
{
  lock_acquire(&filesys_lock);
  bool success = filesys_remove(file);
  lock_release(&filesys_lock);
  return success;
}

int open (const char *file)
{
  lock_acquire(&filesys_lock);
  struct file *f = filesys_open(file);
  if (!f)
    {
      lock_release(&filesys_lock);
      return ERROR;
    }
  int fd = process_add_file(f);
  lock_release(&filesys_lock);
  return fd;
}

int filesize (int fd)
{
  lock_acquire(&filesys_lock);
  struct file *f = process_get_file(fd);
  if (!f)
    {
      lock_release(&filesys_lock);
      return ERROR;
    }
  int size = file_length(f);
  lock_release(&filesys_lock);
  return size;
}

int read (int fd, void *buffer, unsigned size)
{
  if (fd == STDIN_FILENO)
    {
      unsigned i;
      uint8_t* local_buffer = (uint8_t *) buffer;
      for (i = 0; i < size; i++)
		{
		  local_buffer[i] = input_getc();
		}
      return size;
    }
  lock_acquire(&filesys_lock);
  struct file *f = process_get_file(fd);
  if (!f)
    {
      lock_release(&filesys_lock);
      return ERROR;
    }
  int bytes = file_read(f, buffer, size);
  lock_release(&filesys_lock);
  return bytes;
}

int write (int fd, const void *buffer, unsigned size)
{
  if (fd == STDOUT_FILENO)
    {
      putbuf(buffer, size);
      return size;
    }
  lock_acquire(&filesys_lock);
  struct file *f = process_get_file(fd);
  if (!f)
    {
      lock_release(&filesys_lock);
      return ERROR;
    }
  int bytes = file_write(f, buffer, size);
  lock_release(&filesys_lock);
  return bytes;
}

void seek (int fd, unsigned position)
{
  lock_acquire(&filesys_lock);
  struct file *f = process_get_file(fd);
  if (!f)
    {
      lock_release(&filesys_lock);
      return;
    }
  file_seek(f, position);
  lock_release(&filesys_lock);
}

unsigned tell (int fd)
{
  lock_acquire(&filesys_lock);
  struct file *f = process_get_file(fd);
  if (!f)
    {
      lock_release(&filesys_lock);
      return ERROR;
    }
  off_t offset = file_tell(f);
  lock_release(&filesys_lock);
  return offset;
}

void close (int fd)
{
  lock_acquire(&filesys_lock);
  process_close_file(fd);
  lock_release(&filesys_lock);
}


int process_add_file (struct file *f)
{
  struct process_file *pf = malloc(sizeof(struct process_file));
  pf->file = f;
  pf->fd = thread_current()->fd;
  thread_current()->fd++;
  list_push_back(&thread_current()->file_list, &pf->elem);
  return pf->fd;
}

struct file* process_get_file (int fd)
{
  struct thread *t = thread_current();
  struct list_elem *e;

  for (e = list_begin (&t->file_list); e != list_end (&t->file_list);
       e = list_next (e))
        {
          struct process_file *pf = list_entry (e, struct process_file, elem);
          if (fd == pf->fd)
	    {
	      return pf->file;
	    }
        }
  return NULL;
}

void process_close_file (int fd)
{
  struct thread *t = thread_current();
  struct list_elem *next, *e = list_begin(&t->file_list);

  while (e != list_end (&t->file_list))
    {
      next = list_next(e);
      struct process_file *pf = list_entry (e, struct process_file, elem);
      if (fd == pf->fd || fd == CLOSE_ALL)
	{
	  file_close(pf->file);
	  list_remove(&pf->elem);
	  free(pf);
	  if (fd != CLOSE_ALL)
	    {
	      return;
	    }
	}
      e = next;
    }
}

struct child_process* add_child_process (int pid)
{
  struct child_process* cp = malloc(sizeof(struct child_process));
  cp->pid = pid;
  cp->load = NOT_LOADED;
  cp->wait = false;
  cp->exit = false;
  lock_init(&cp->wait_lock);
  list_push_back(&thread_current()->child_list,
		 &cp->elem);
  return cp;
}

struct child_process* get_child_process (int pid)
{
  struct thread *t = thread_current();
  struct list_elem *e;

  for (e = list_begin (&t->child_list); e != list_end (&t->child_list);
       e = list_next (e))
        {
          struct child_process *cp = list_entry (e, struct child_process, elem);
          if (pid == cp->pid)
	    {
	      return cp;
	    }
        }
  return NULL;
}

void remove_child_process (struct child_process *cp)
{
  list_remove(&cp->elem);
  free(cp);
}

void remove_child_processes (void)
{
  struct thread *t = thread_current();
  struct list_elem *next, *e = list_begin(&t->child_list);

  while (e != list_end (&t->child_list))
    {
      next = list_next(e);
      struct child_process *cp = list_entry (e, struct child_process,
					     elem);
      list_remove(&cp->elem);
      free(cp);
      e = next;
    }
}

void get_args(struct intr_frame *f, int *arg, int n)
{
  int i;
  int *ptr;
  for (i = 0; i < n; i++)
    {
      ptr = (int *) f->esp + i + 1;
      arg[i] = *ptr;
    }
}

/*void syscall_mine(void)
{	
	printf("my system call executed");
}*/


static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  int *p = f->esp;
  int args[3];
  
  switch(*p)
  {
	
	case SYS_HALT:
		printf("halt called!!");
		halt(); 
		break;
	
	case SYS_EXIT: 
		get_args(f, args, 1);
		exit(args[0]);
		break;
	
	case SYS_EXEC: 
		get_args(f, args, 1);
		f->eax = exec((const char *) args[0]); 
		break;
	
    case SYS_WAIT:
		get_args(f, args, 1);
		f->eax = wait(args[0]);
		break;

    case SYS_CREATE:
		get_args(f, args, 2);
		f->eax = create((const char *)args[0], (unsigned) args[1]);
		if(f->eax == 1)
			printf("File was created sucessfully");
		break;
      
    case SYS_REMOVE:
		get_args(f, args, 1);
		f->eax = remove((const char *) args[0]);
		break;
     
    case SYS_OPEN:      
		get_args(f, args, 1);
		f->eax = open((const char *) args[0]);
		if(f->eax == ERROR)
			printf("Error in opening the requested file\n");
		break; 		
		  
    case SYS_FILESIZE:
		get_args(f, args, 1);
		f->eax = filesize(args[0]);
		if(f->eax == ERROR)
			printf("Error in calculating filesize of the requested file\n");
		break;
      
    case SYS_READ:
		get_args(f, args, 3);
		f->eax = read(args[0], (void *) args[1], (unsigned) args[2]);
		break;

    case SYS_WRITE: 
		get_args(f, args, 3);
		f->eax = write(args[0], (const void *) args[1],(unsigned) args[2]);
		break;
		  
	case SYS_SEEK:
		get_args(f, args, 2);
		seek(args[0], (unsigned) args[1]);
		break;
      
    case SYS_TELL:
		get_args(f, args, 1);
		f->eax = tell(args[0]);
		break;
      
	case SYS_CLOSE:
		get_args(f, args, 1);
		close(args[0]);
		break;/*
	case SYS_MY:
		syscall_mine();
		break;
      */
  }	
  
  thread_exit ();
}

