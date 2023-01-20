# FlatBuffer Verification

Used to check whether FlatBuffer messages created by [python-streaming-data-types](https://github.com/ess-dmsc/python-streaming-data-types)
are verifiable.

## How to use
From Python, use the python-streaming-data-types module to dump a FlatBuffer message to file.
For example, for the x5f2 schema:
```
from streaming_data_types.status_x5f2 import serialise_x5f2

ans = serialise_x5f2("name", "v1", "ser", "host", 12345, 100, "{}")

with open("fb_out", "wb") as f:
    f.write(ans)
```

Then the same file can be loaded using this program to see if it verifies.

## Adding a schema for verification
Assumes the schema is already part of the streaming-data-types Conan package.

* Create an .h and .cpp file for the schema
* Copy the code from one of existing schemas, e.g. hs00.h and hs00.cpp
* Update the code so it is correct for the schema
* Add the files to the CMake file
* Add a clause in `main.cpp`'s `verify_message` function for the schema
