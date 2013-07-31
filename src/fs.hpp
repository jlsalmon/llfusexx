//------------------------------------------------------------------------------
// Copyright (c) 2011-2012 by European Organization for Nuclear Research (CERN)
// Author: Justin Salmon <jsalmon@cern.ch>
//------------------------------------------------------------------------------
// XRootD is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// XRootD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with XRootD.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#ifndef __LLFUSEXX_FS_HPP__
#define __LLFUSEXX_FS_HPP__

#ifndef FUSE_USE_VERSION
#ifdef __APPLE__
#define FUSE_USE_VERSION 27
#else
#define FUSE_USE_VERSION 26
#endif
#endif

#include <fuse_lowlevel.h>
#include <cstdlib>

namespace llfusexx
{
  //----------------------------------------------------------------------------
  //!
  //----------------------------------------------------------------------------
  template <typename T>
  class fs
  {
    private:

      //------------------------------------------------------------------------
      //!
      //------------------------------------------------------------------------
      struct fuse_lowlevel_ops operations;

      //------------------------------------------------------------------------
      //!
      //------------------------------------------------------------------------
      const fuse_lowlevel_ops* get_operations()
      {
        return &operations;
      }

    public:

      //------------------------------------------------------------------------
      //!
      //------------------------------------------------------------------------
      fs()
      {
        operations.getattr = &T::getattr;
        operations.readdir = &T::readdir;
        operations.read    = &T::read;
        operations.write   = &T::write;
        operations.open    = &T::open;
        operations.lookup  = &T::lookup;
      }

      //------------------------------------------------------------------------
      //!
      //------------------------------------------------------------------------
      int daemonize( int argc, char* argv[] )
      {
        struct fuse_args  args = FUSE_ARGS_INIT(argc, argv);
        struct fuse_chan *channel;
        char             *mountpoint;
        int               error = -1;

        if( fuse_parse_cmdline( &args, &mountpoint, NULL, NULL ) != -1
            && ( channel = fuse_mount( mountpoint, &args ) ) != NULL )
        {
          struct fuse_session *session;

          session = fuse_lowlevel_new( &args,
                                       get_operations(),
                                       sizeof(fs::operations),
                                       NULL );
          if( session != NULL )
          {
            if( fuse_set_signal_handlers( session ) != -1 )
            {
              fuse_session_add_chan( session, channel );
              error = fuse_session_loop_mt( session );
              fuse_remove_signal_handlers( session );
              fuse_session_remove_chan( channel );
            }
            fuse_session_destroy( session );
          }
          fuse_unmount( mountpoint, channel );
        }
        fuse_opt_free_args( &args );

        return error ? 1 : 0;
      }
  };
}

#endif /* __LLFUSEXX_FS_HPP__ */
