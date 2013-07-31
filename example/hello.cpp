#include "fs.hpp"

//------------------------------------------------------------------------------
//! Curiously recurring templates....
//------------------------------------------------------------------------------
class hellofs : public llfusexx::fs<hellofs>
{
  public:
    //--------------------------------------------------------------------------
    //!
    //--------------------------------------------------------------------------
    static void readdir( fuse_req_t             req,
                         fuse_ino_t             ino,
                         size_t                 size,
                         off_t                  off,
                         struct fuse_file_info *fi ) {};

    //--------------------------------------------------------------------------
    //!
    //--------------------------------------------------------------------------
    static void open( fuse_req_t             req,
                      fuse_ino_t             ino,
                      struct fuse_file_info *fi ) {};

    //--------------------------------------------------------------------------
    //!
    //--------------------------------------------------------------------------
    static void read( fuse_req_t             req,
                      fuse_ino_t             ino,
                      size_t                 size,
                      off_t                  off,
                      struct fuse_file_info *fi ) {};

    //--------------------------------------------------------------------------
    //!
    //--------------------------------------------------------------------------
    static void write( fuse_req_t             req,
                       fuse_ino_t             ino,
                       const char            *buf,
                       size_t                 size,
                       off_t                  off,
                       struct fuse_file_info *fi ) {};

    //--------------------------------------------------------------------------
    //!
    //--------------------------------------------------------------------------
    static void getattr( fuse_req_t             req,
                         fuse_ino_t             ino,
                         struct fuse_file_info *fi ) {};

    //--------------------------------------------------------------------------
    //!
    //--------------------------------------------------------------------------
    static void lookup( fuse_req_t  req,
                        fuse_ino_t  parent,
                        const char *name ) {};
};

int main( int argc, char* argv[] )
{
  hellofs fs;

  //----------------------------------------------------------------------------
  //! Runs the daemon at the mountpoint specified in argv and with other
  //! options if specified
  //----------------------------------------------------------------------------
  return fs.daemonize( argc, argv );
}
