/// \file uds_connection.h
/// \brief Declares the UnixDomainSocketConnection class.

/***********************************************************************
 Copyright (c) 2007-2008 by Educational Technology Resources, Inc.
 Others may also hold copyrights on code in this file.  See the
 CREDITS.txt file in the top directory of the distribution for details.

 This file is part of MySQL++.

 MySQL++ is free software; you can redistribute it and/or modify it
 under the terms of the GNU Lesser General Public License as published
 by the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 MySQL++ is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with MySQL++; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
 USA
***********************************************************************/

#if !defined(MYSQLPP_UDS_CONNECTION_H)
#define MYSQLPP_UDS_CONNECTION_H

#include "connection.h"

namespace mysqlpp
{

/// \brief Specialization of \c Connection for Unix domain sockets
///
/// This class just simplifies the connection creation interface of
/// \c Connection.  It does not add new functionality.

class UnixDomainSocketConnection : public Connection
{
public:
    /// \brief Create object without connecting it to the MySQL server.
    UnixDomainSocketConnection() :
        Connection()
    {
    }

    /// \brief Create object and connect to database server over Unix
    /// domain sockets in one step.
    ///
    /// \param path filesystem path to socket
    /// \param db name of database to use
    /// \param user user name to log in under, or 0 to use the user
    ///		name the program is running under
    /// \param password password to use when logging in
    ///
    /// \b BEWARE: These parameters are not in the same order as those
    /// in the corresponding constructor for Connection.  This is a
    /// feature, not a bug. :)
    UnixDomainSocketConnection(const char* path, const char* db = 0,
                               const char* user = 0, const char* password = 0) :
        Connection()
    {
        connect(path, db, user, password);
    }

    /// \brief Establish a new connection using the same parameters as
    /// an existing connection.
    ///
    /// \param other pre-existing connection to clone
    UnixDomainSocketConnection(const UnixDomainSocketConnection& other) :
        Connection(other)
    {
    }

    /// \brief Destroy object
    ~UnixDomainSocketConnection() { }

    /// \brief Connect to database after object is created.
    ///
    /// It's better to use the connect-on-create constructor if you can.
    /// See its documentation for the meaning of these parameters.
    ///
    /// If you call this method on an object that is already connected
    /// to a database server, the previous connection is dropped and a
    /// new connection is established.
    bool connect(const char* path, const char* db = 0,
                 const char* user = 0, const char* password = 0);

    /// \brief Check that the given path names a Unix domain socket and
    /// that we have read-write permission for it
    ///
    /// \param path the filesystem path to the socket
    /// \param error on failure, reason is placed here; take default
    /// if you do not need a reason if it fails
    ///
    /// \return false if address fails to pass sanity checks
    static bool is_socket(const char* path, std::string* error = 0);

private:
    /// \brief Provide uncallable versions of the parent class ctors we
    /// don't want to provide so we don't get warnings about hidden
    /// overloads with some compilers
    UnixDomainSocketConnection(bool) { }
    UnixDomainSocketConnection(const char*, const char*, const char*,
                               const char*, unsigned int) { }

    /// \brief Explicitly override parent class version so we don't get
    /// complaints about hidden overloads with some compilers
    bool connect(const char*, const char*, const char*, const char*,
                 unsigned int)
    {
        return false;
    }
};


} // end namespace mysqlpp

#endif // !defined(MYSQLPP_UDS_CONNECTION_H)

