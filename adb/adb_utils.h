/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ADB_UTILS_H_
#define _ADB_UTILS_H_

#include <string>

#include <android-base/macros.h>

void close_stdin();

bool getcwd(std::string* cwd);
bool directory_exists(const std::string& path);

// Like the regular basename and dirname, but thread-safe on all
// platforms and capable of correctly handling exotic Windows paths.
std::string adb_basename(const std::string& path);
std::string adb_dirname(const std::string& path);

bool mkdirs(const std::string& path);

std::string escape_arg(const std::string& s);

std::string dump_hex(const void* ptr, size_t byte_count);

std::string perror_str(const char* msg);

bool set_file_block_mode(int fd, bool block);

extern int adb_close(int fd);

// Helper to automatically close an FD when it goes out of scope.
class ScopedFd {
  public:
    ScopedFd() {
    }

    ~ScopedFd() {
        Reset();
    }

    void Reset(int fd = -1) {
        if (fd != fd_) {
            if (valid()) {
                adb_close(fd_);
            }
            fd_ = fd;
        }
    }

    int Release() {
        int temp = fd_;
        fd_ = -1;
        return temp;
    }

    bool valid() const {
        return fd_ >= 0;
    }

    int fd() const {
        return fd_;
    }

  private:
    int fd_ = -1;

    DISALLOW_COPY_AND_ASSIGN(ScopedFd);
};

#endif
