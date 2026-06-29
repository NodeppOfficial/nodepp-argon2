
#include <nodepp/nodepp.h>
#include <nodepp/encoder.h>
#include <argon/argon2.h>

using namespace nodepp;

void onMain() {

    argon2_t argon( 32 ); auto pass = argon.hash( "password" );
    console::log( pass, argon.verify( pass, "password" ) ? "valid" : "invalid" );

}