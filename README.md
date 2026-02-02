# Argon2 for NodePP: Secure Password Hashing in C++

This project provides a robust and easy-to-use Argon2 password hashing library specifically designed for the NodePP environment. Argon2 is a modern, memory-hard algorithm that won the Password Hashing Competition and is recommended for its strong security properties against various attacks, including GPU cracking. By bringing Argon2 to NodePP, this library enables developers to leverage the performance of C++ for critical security tasks within their asynchronous, event-driven applications.

## Dependencies & Cmake Integration
```bash
# Argon2
    🪟: pacman -S mingw-w64-ucrt-x86_64-argon2
    🐧: sudo apt install libargon2-dev
```
```bash
include(FetchContent)

FetchContent_Declare(
	nodepp
	GIT_REPOSITORY   https://github.com/NodeppOfficial/nodepp
	GIT_TAG          origin/main
	GIT_PROGRESS     ON
)
FetchContent_MakeAvailable(nodepp)

FetchContent_Declare(
	nodepp-argon
	GIT_REPOSITORY   https://github.com/NodeppOfficial/nodepp-argon
	GIT_TAG          origin/main
	GIT_PROGRESS     ON
)
FetchContent_MakeAvailable(nodepp-argon)

#[...]

target_link_libraries( #[...]
	PUBLIC nodepp nodepp-argon #[...]
)
```

## Key Features
- **Secure Password Hashing:** Implements the Argon2 algorithm, a state-of-the-art password hashing function.
- **Multiple Variants:** Likely to support Argon2i, Argon2d, and Argon2id variants, allowing selection based on specific security requirements.
- **Configurable Parameters:** Provides options to adjust time cost, memory cost, and parallelism to fine-tune security levels and performance.
- **NodePP Integration:** Seamlessly integrates with NodePP's asynchronous and event-driven architecture.
- **High Performance:** Benefits from C++ implementation for potentially faster hashing and verification compared to pure JavaScript solutions.
- **Simple API:** Offers an intuitive API for hashing passwords and verifying them against stored hashes within NodePP applications.
- **Memory Hardness:** Leverages Argon2's memory-hard design to resist attacks that rely on specialized hardware.

## Usage 
```cpp
#include <nodepp/nodepp.h>
#include <nodepp/encoder.h>
#include <argon/argon2.h>

using namespace nodepp;

void onMain() {

    argon2_t argon( 32 ); 
    console::log( argon.hash( "password" ) );

}
```

## Build & Run
```bash
🪟: g++ -o main main.cpp -I ./include -largon2 -lws2_32 ; ./main
🐧: g++ -o main main.cpp -I ./include -largon2 ; ./main
```

## License
**Nodepp-Argon2** is distributed under the MIT License. See the LICENSE file for more details.
