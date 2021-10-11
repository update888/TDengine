/*
 * Copyright (c) 2019 TAOS Data, Inc. <cli@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TD_RAFT_IMPL_H
#define TD_RAFT_IMPL_H

#include "raft.h"
#include "tqueue.h"

typedef int64_t   RaftIndex;
typedef uint64_t  RaftTerm;

typedef enum RaftRole {
  RAFT_FOLLOWER   = 1,
  RAFT_CANDIDATE  = 2,
  RAFT_LEADER     = 3,
} RaftRole;

/* raft log entry */
typedef struct RaftEntry {
  RaftTerm term;
  RaftBuffer buffer;
} RaftEntry;

/* raft log entry with reference count */
typedef struct RaftRefEntry {
  RaftEntry* entry;

  unsigned int refCount;
} RaftRefEntry;

/* in-memory raft log storage */
typedef struct RaftLog {
  /* Circular buffer of log entries */
  RaftRefEntry *entries;

  /* size of Circular buffer */
  size_t size;

  /* Indexes of used slots [front, back) */
  size_t front, back;

  /* Index of first entry is offset+1 */
  RaftIndex offset;

  /* last index and term of snapshot */
  struct {
    RaftIndex lastIndex;
    RaftTerm  lastTerm;
  } snapshot;
} RaftLog;

// raft core algorithm struct
typedef struct RaftCore {
  RaftRole role;

  // user define state machine
  RaftFSM* pFSM;
  
  RaftLog  log;
} RaftCore;

struct RaftNode {
  // the cluster configuration
  RaftConfiguration* cluster;

  // node options
  RaftNodeOptions options;

  // node worker thread
  pthread_t thread;

  // node worker message queue
  taos_qset  msgQset;
  taos_qall  msgQall;
  taos_queue msgQueue;

  // raft core algorithm
  RaftCore* raftCore;
};

struct Raft {
  RaftNode* nodes;
};

#endif /* TD_RAFT_IMPL_H */