#include "fs.hpp"

//------------------------------------------------------------------------------
//! Curiously recurring templates....
//------------------------------------------------------------------------------
class hellofs : public llfusexx::fs<hellofs>
{
  public:
    //--------------------------------------------------------------------------
    // Get file attributes
    //--------------------------------------------------------------------------
    static void getattr (fuse_req_t             req,
                         fuse_ino_t             ino,
                         struct fuse_file_info *fi)
    {
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
    }

    //--------------------------------------------------------------------------
    // Lookup an entry
    //--------------------------------------------------------------------------
    static void lookup (fuse_req_t  req,
                        fuse_ino_t  parent,
                        const char *name)
    {
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
    }

    //--------------------------------------------------------------------------
    // Drop directory view
    //--------------------------------------------------------------------------
    static void releasedir (fuse_req_t             req,
                            fuse_ino_t             ino,
                            struct fuse_file_info *fi)
    {
    }


    //--------------------------------------------------------------------------
    // Return statistics about the filesystem
    //--------------------------------------------------------------------------
    static void statfs (fuse_req_t req, fuse_ino_t ino)
    {
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
    }


    //--------------------------------------------------------------------------
    // Create a directory with a given name
    //--------------------------------------------------------------------------
    static void mkdir (fuse_req_t  req,
                       fuse_ino_t  parent,
                       const char *name,
                       mode_t      mode)
    {
    }


    //--------------------------------------------------------------------------
    // Remove (delete) the given file, symbolic link, hard link, or special node
    //--------------------------------------------------------------------------
    static void unlink (fuse_req_t req, fuse_ino_t parent, const char *name)
    {
    }


    //--------------------------------------------------------------------------
    // Remove the given directory
    //--------------------------------------------------------------------------
    static void rmdir (fuse_req_t req, fuse_ino_t parent, const char *name)
    {
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
    }


    //--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
    static void access (fuse_req_t req, fuse_ino_t ino, int mask)
    {
    }


    //--------------------------------------------------------------------------
    // Open a file
    //--------------------------------------------------------------------------
    static void open (fuse_req_t             req,
                      fuse_ino_t             ino,
                      struct fuse_file_info *fi)
    {
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
    }


    //--------------------------------------------------------------------------
    // Release is called when FUSE is completely done with a file; at that point,
    // you can free up any temporarily allocated data structures.
    //--------------------------------------------------------------------------
    static void release (fuse_req_t             req,
                         fuse_ino_t             ino,
                         struct fuse_file_info *fi)
    {
    }


    //--------------------------------------------------------------------------
    // Flush any dirty information about the file to disk
    //--------------------------------------------------------------------------
    static void fsync (fuse_req_t             req,
                       fuse_ino_t             ino,
                       int                    datasync,
                       struct fuse_file_info *fi)
    {
    }


    //--------------------------------------------------------------------------
    // Forget inode <-> path mapping
    //--------------------------------------------------------------------------
    static void forget (fuse_req_t req, fuse_ino_t ino, unsigned long nlookup)
    {
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
    }


    //--------------------------------------------------------------------------
    // Get an extended attribute
    //--------------------------------------------------------------------------
    static void getxattr (fuse_req_t  req,
                          fuse_ino_t  ino,
                          const char *xattr_name,
                          size_t      size)
    {
    }


    //--------------------------------------------------------------------------
    // List extended attributes
    //--------------------------------------------------------------------------
    static void listxattr (fuse_req_t req, fuse_ino_t ino, size_t size)
    {
    }


    //--------------------------------------------------------------------------
    // Remove extended attribute
    //--------------------------------------------------------------------------
    static void removexattr (fuse_req_t  req,
                             fuse_ino_t  ino,
                             const char *xattr_name)
    {
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
