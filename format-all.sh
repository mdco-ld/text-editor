#!/bin/bash

clang-format -i $(find src -type f) && clang-format -i $(find include -type f)
