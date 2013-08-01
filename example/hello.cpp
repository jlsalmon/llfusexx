#include "llfusexx.hpp"
#include <iostream>
#include <cstring>
#include <cerrno>
#include <cassert>
#include <cstdio>

static const char *hello_str  = "Hello World!\n";
static const char *hello_name = "hello";

//------------------------------------------------------------------------------
//! Curiously recurring templates....
//------------------------------------------------------------------------------
class hellofs : public llfusexx::fs<hellofs>
{
  public:
    //--------------------------------------------------------------------------
    // Constructor
    //--------------------------------------------------------------------------
    hellofs() {};

    //--------------------------------------------------------------------------
    // Destructor
    //--------------------------------------------------------------------------
    virtual ~hellofs() {};

    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    static int hello_stat( fuse_ino_t ino, struct stat *stbuf )
    {
      std::cout << "hello_stat()" << std::endl;

      stbuf->st_ino = ino;
      switch( ino )
      {
      case 1:
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        break;

      case 2:
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen( hello_str );
        break;

      default:
        return -1;
      }
      return 0;
    }

    //--------------------------------------------------------------------------
    // Initialize filesystem
    //--------------------------------------------------------------------------
    static void init (void *userdata, struct fuse_conn_info *conn)
    {
      std::cout << "init()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Clean up filesystem
    //--------------------------------------------------------------------------
    static void destroy (void *userdata)
    {
      std::cout << "destroy()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Get file attributes
    //--------------------------------------------------------------------------
    static void getattr (fuse_req_t             req,
                         fuse_ino_t             ino,
                         struct fuse_file_info *fi)
    {
      struct stat stbuf;
      std::cout << "getattr()" << std::endl;

      (void) fi;

      memset( &stbuf, 0, sizeof( stbuf ) );
      if( hello_stat( ino, &stbuf ) == -1 )
        fuse_reply_err( req, ENOENT );
      else
        fuse_reply_attr( req, &stbuf, 1.0 );
    }

    //--------------------------------------------------------------------------
    // Change attributes of a file
    //--------------------------------------------------------------------------
    static void setattr (fuse_req_t             req,
                         fuse_ino_t             ino,
                         struct stat           *attr,
                         int                    to_set,
                         struct fuse_file_info *fi)
    {
      std::cout << "setattr()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Lookup an entry
    //--------------------------------------------------------------------------
    static void lookup (fuse_req_t  req,
                        fuse_ino_t  parent,
                        const char *name)
    {
      struct fuse_entry_param e;
      std::cout << "lookup()" << std::endl;

      if( parent != 1 || strcmp( name, hello_name ) != 0 )
        fuse_reply_err( req, ENOENT );
      else
      {
        memset( &e, 0, sizeof( e ) );
        e.ino = 2;
        e.attr_timeout = 1.0;
        e.entry_timeout = 1.0;
        hello_stat( e.ino, &e.attr );

        fuse_reply_entry( req, &e );
      }
    }


    struct dirbuf
    {
        char *p;
        size_t size;
    };

    static void dirbuf_add( fuse_req_t req, struct dirbuf *b, const char *name,
        fuse_ino_t ino )
    {
      std::cout << "dirbuf_add()" << std::endl;

      struct stat stbuf;
      size_t oldsize = b->size;
      b->size += fuse_add_direntry( req, NULL, 0, name, NULL, 0 );
      char *newp = (char*) realloc( b->p, b->size );
      if( !newp )
      {
        fprintf( stderr, "*** fatal error: cannot allocate memory\n" );
        abort();
      }
      b->p = newp;
      memset( &stbuf, 0, sizeof( stbuf ) );
      stbuf.st_ino = ino;
      fuse_add_direntry( req, b->p + oldsize, b->size - oldsize, name, &stbuf,
          b->size );
    }

    #define min(x, y) ((x) < (y) ? (x) : (y))

    static int reply_buf_limited( fuse_req_t req, const char *buf,
        size_t bufsize, off_t off, size_t maxsize )
    {
      if( off < bufsize )
        return fuse_reply_buf( req, buf + off, min(bufsize - off, maxsize) );
      else
        return fuse_reply_buf( req, NULL, 0 );
    }

    //--------------------------------------------------------------------------
    // Read the entries from a directory
    //--------------------------------------------------------------------------
    static void readdir (fuse_req_t             req,
                         fuse_ino_t             ino,
                         size_t                 size,
                         off_t                  off,
                         struct fuse_file_info *fi)
    {
      (void) fi;
      std::cout << "readdir()" << std::endl;

      if( ino != 1 )
        fuse_reply_err( req, ENOTDIR );
      else
      {
        struct dirbuf b;

        memset( &b, 0, sizeof( b ) );
        dirbuf_add( req, &b, ".", 1 );
        dirbuf_add( req, &b, "..", 1 );
        dirbuf_add( req, &b, hello_name, 2 );
        reply_buf_limited( req, b.p, b.size, off, size );
        free( b.p );
      }
    }

    //--------------------------------------------------------------------------
    // Drop directory view
    //--------------------------------------------------------------------------
    static void releasedir (fuse_req_t             req,
                            fuse_ino_t             ino,
                            struct fuse_file_info *fi)
    {
      std::cout << "releasedir()" << std::endl;
      fuse_reply_err (req, 0);
    }

    //--------------------------------------------------------------------------
    // Return statistics about the filesystem
    //--------------------------------------------------------------------------
    static void statfs (fuse_req_t req, fuse_ino_t ino)
    {
      std::cout << "statfs()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Make a special (device) file, FIFO, or socket
    //--------------------------------------------------------------------------
    static void mknod (fuse_req_t  req,
                       fuse_ino_t  parent,
                       const char *name,
                       mode_t      mode,
                       dev_t       rdev)
    {
      std::cout << "mknod()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Create a directory with a given name
    //--------------------------------------------------------------------------
    static void mkdir (fuse_req_t  req,
                       fuse_ino_t  parent,
                       const char *name,
                       mode_t      mode)
    {
      std::cout << "mkdir()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Remove (delete) the given file, symbolic link, hard link, or special node
    //--------------------------------------------------------------------------
    static void unlink (fuse_req_t req, fuse_ino_t parent, const char *name)
    {
      std::cout << "unlink()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Remove the given directory
    //--------------------------------------------------------------------------
    static void rmdir (fuse_req_t req, fuse_ino_t parent, const char *name)
    {
      std::cout << "rmdir()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Rename the file, directory, or other object
    //--------------------------------------------------------------------------
    static void rename (fuse_req_t  req,
                        fuse_ino_t  parent,
                        const char *name,
                        fuse_ino_t  newparent,
                        const char *newname)
    {
      std::cout << "rename()" << std::endl;
    }

    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    static void access (fuse_req_t req, fuse_ino_t ino, int mask)
    {
      std::cout << "access()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Open a file
    //--------------------------------------------------------------------------
    static void open (fuse_req_t             req,
                      fuse_ino_t             ino,
                      struct fuse_file_info *fi)
    {
      std::cout << "open()" << std::endl;

      if( ino != 2 )
        fuse_reply_err( req, EISDIR );
      else if( ( fi->flags & 3 ) != O_RDONLY )
        fuse_reply_err( req, EACCES );
      else
        fuse_reply_open( req, fi );
    }

    //--------------------------------------------------------------------------
    // Open a directory
    //--------------------------------------------------------------------------
    static void opendir (fuse_req_t             req,
                         fuse_ino_t             ino,
                         struct fuse_file_info *fi)
    {
      std::cout << "opendir()" << std::endl;
      fuse_reply_open( req, fi );
    }

    //--------------------------------------------------------------------------
    // Read from file. Returns the number of bytes transferred, or 0 if offset
    // was at or beyond the end of the file.
    //--------------------------------------------------------------------------
    static void read (fuse_req_t             req,
                      fuse_ino_t             ino,
                      size_t                 size,
                      off_t                  off,
                      struct fuse_file_info *fi)
    {
      (void) fi;
      std::cout << "read()" << std::endl;

      assert( ino == 2 );
      reply_buf_limited( req, hello_str, strlen( hello_str ), off, size );
    }

    //--------------------------------------------------------------------------
    // Write function
    //--------------------------------------------------------------------------
    static void write (fuse_req_t             req,
                       fuse_ino_t             ino,
                       const char            *buf,
                       size_t                 size,
                       off_t                  off,
                       struct fuse_file_info *fi)
    {
      std::cout << "write()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Release is called when FUSE is completely done with a file; at that point,
    // you can free up any temporarily allocated data structures.
    //--------------------------------------------------------------------------
    static void release (fuse_req_t             req,
                         fuse_ino_t             ino,
                         struct fuse_file_info *fi)
    {
      std::cout << "release()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Flush any dirty information about the file to disk
    //--------------------------------------------------------------------------
    static void fsync (fuse_req_t             req,
                       fuse_ino_t             ino,
                       int                    datasync,
                       struct fuse_file_info *fi)
    {
      std::cout << "fsync()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Forget inode <-> path mapping
    //--------------------------------------------------------------------------
    static void forget (fuse_req_t req, fuse_ino_t ino, unsigned long nlookup)
    {
      std::cout << "forget()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Called on each close so that the filesystem has a chance to report delayed errors
    // Important: there may be more than one flush call for each open.
    // Note: There is no guarantee that flush will ever be called at all!
    //--------------------------------------------------------------------------
    static void flush (fuse_req_t             req,
                       fuse_ino_t             ino,
                       struct fuse_file_info *fi)
    {
      std::cout << "flush()" << std::endl;
      fuse_reply_err (req, 0);
    }

    //--------------------------------------------------------------------------
    // Get an extended attribute
    //--------------------------------------------------------------------------
    static void getxattr (fuse_req_t  req,
                          fuse_ino_t  ino,
                          const char *xattr_name,
                          size_t      size)
    {
      std::cout << "getxattr()" << std::endl;
      fuse_reply_err (req, ENODATA);
      return;
    }

    //--------------------------------------------------------------------------
    // List extended attributes
    //--------------------------------------------------------------------------
    static void listxattr (fuse_req_t req, fuse_ino_t ino, size_t size)
    {
      std::cout << "listxattr()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Remove extended attribute
    //--------------------------------------------------------------------------
    static void removexattr (fuse_req_t  req,
                             fuse_ino_t  ino,
                             const char *xattr_name)
    {
      std::cout << "removexattr()" << std::endl;
    }

    //--------------------------------------------------------------------------
    // Set extended attribute
    //--------------------------------------------------------------------------
    static void setxattr (fuse_req_t  req,
                          fuse_ino_t  ino,
                          const char *xattr_name,
                          const char *xattr_value,
                          size_t      size,
                          int         flags)
    {
      std::cout << "setxattr()" << std::endl;
    }
};

int main( int argc, char *argv[] )
{
  hellofs fs;

  //----------------------------------------------------------------------------
  //! Runs the daemon at the mountpoint specified in argv and with other
  //! options if specified
  //----------------------------------------------------------------------------
  return fs.daemonize( argc, argv );
}
