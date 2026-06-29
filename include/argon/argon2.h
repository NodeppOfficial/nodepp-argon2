/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_ARGON_2
#define NODEPP_ARGON_2

/*────────────────────────────────────────────────────────────────────────────*/

#include <nodepp/nodepp.h>
#include <nodepp/encoder.h>
#include <argon2.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class argon2_t {
protected:

    struct NODE {
        ptr_t<uchar_32> conf;
        ptr_t<uchar>   hash;
    };  ptr_t<NODE> obj;

public:

    /*.........................................................................*/

    argon2_t( uchar_32 size, uchar_32 t_cost, uchar_32 m_cost, uchar_32 parallelism ) : obj( new NODE() ) {
        obj->conf = ptr_t<uchar_32>({ t_cost, m_cost, parallelism });
        obj->hash = ptr_t<uchar>( size, '\0' );
    }

    argon2_t( uchar_32 size ) : obj( new NODE() ) {
        obj->hash = ptr_t<uchar>  ( size, '\0' );
        obj->conf = ptr_t<uchar_32>({ 2, 64, 1 });
    }

    /*.........................................................................*/

    string_t hash( const string_t& pass, const string_t& salt, const string_t& secr, const string_t& addr ) const noexcept { 
    string_t _salt = salt.empty() ? string_t( obj->hash.size(), '\0' ) : salt;

        argon2_context ctx = { 
                obj->hash.get(), (uchar_32) obj->hash.size(), 
            (uchar*) pass.get(), (uchar_32) pass.size(),
            (uchar*)_salt.get(), (uchar_32)_salt.size(), 
            (uchar*) secr.get(), (uchar_32) secr.size(), 
            (uchar*) addr.get(), (uchar_32) addr.size(), 
            obj->conf[0], obj->conf[1], obj->conf[2], obj->conf[2], 
            ARGON2_VERSION_13, NULL, NULL, ARGON2_DEFAULT_FLAGS
        };  int rc = argon2i_ctx( &ctx ); 
        
        if( ARGON2_OK != rc ){ return nullptr; }
        return encoder::hex::get( obj->hash );

    }

    string_t hash( const string_t& pass, const string_t& salt ) const { 
      return hash( pass, salt, nullptr, nullptr );
    }

    string_t hash( const string_t& pass ) const { 
      return hash( pass, nullptr, nullptr, nullptr );
    }

    /*.........................................................................*/

    template< class... T >
    bool verify( const string_t& data, const T&... args ) const noexcept { 
         return data==hash( args... ); 
    }

};}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace argon2 { namespace hash {

    template< class... T >
    string_t get( uchar_32 size, T... args ) {
    argon2_t argon(size); return argon.hash( args... ); }

}}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif