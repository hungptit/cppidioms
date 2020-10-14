#include <cstdio>
#include <cstdlib>

#include "mdbx.h"

int main() {
  int rc;
  MDBX_env* env = nullptr;
  MDBX_dbi dbi = 0;
  MDBX_val key, data;
  MDBX_txn* txn = nullptr;
  MDBX_cursor* cursor = nullptr;
  char sval[32];
  char kdata[32];
  char vdata[1024];

  rc = mdbx_env_create(&env);
  if (rc != MDBX_SUCCESS) {
    fprintf(stderr, "mdbx_env_create: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  }
  rc = mdbx_env_open(env, "./example-db",
                     MDBX_NOSUBDIR | MDBX_COALESCE | MDBX_LIFORECLAIM, 0664);
  if (rc != MDBX_SUCCESS) {
    fprintf(stderr, "mdbx_env_open: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  }

  rc = mdbx_txn_begin(env, nullptr, (MDBX_txn_flags_t)0, &txn);
  if (rc != MDBX_SUCCESS) {
    fprintf(stderr, "mdbx_txn_begin: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  }
  rc = mdbx_dbi_open(txn, nullptr, (MDBX_db_flags_t)0, &dbi);
  if (rc != MDBX_SUCCESS) {
    fprintf(stderr, "mdbx_dbi_open: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  }
  
  key.iov_len = sizeof(kdata);
  key.iov_base = kdata;

  data.iov_len = sizeof(vdata);
  data.iov_base = vdata;

  sprintf(kdata, "%d", 123456);
  sprintf(vdata, "This is my super cool test string.");
  rc = mdbx_put(txn, dbi, &key, &data, (MDBX_put_flags_t)0);
  if (rc != MDBX_SUCCESS) {
    fprintf(stderr, "mdbx_put: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  }
  rc = mdbx_txn_commit(txn);
  if (rc) {
    fprintf(stderr, "mdbx_txn_commit: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  }
  txn = nullptr;

  rc = mdbx_txn_begin(env, nullptr, MDBX_TXN_RDONLY, &txn);
  if (rc != MDBX_SUCCESS) {
    fprintf(stderr, "mdbx_txn_begin: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  }
  rc = mdbx_cursor_open(txn, dbi, &cursor);
  if (rc != MDBX_SUCCESS) {
    fprintf(stderr, "mdbx_cursor_open: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  }

  int found = 0;
  while ((rc = mdbx_cursor_get(cursor, &key, &data, MDBX_NEXT)) == 0) {
    printf("key: %p %.*s, data: %p %.*s\n", key.iov_base, (int)key.iov_len,
           (char*)key.iov_base, data.iov_base, (int)data.iov_len,
           (char*)data.iov_base);
    found += 1;
  }
  if (rc != MDBX_NOTFOUND || found == 0) {
    fprintf(stderr, "mdbx_cursor_get: (%d) %s\n", rc, mdbx_strerror(rc));
    exit(1);
  } else {
    rc = MDBX_SUCCESS;
  }
bailout:
  if (cursor) mdbx_cursor_close(cursor);
  if (txn) mdbx_txn_abort(txn);
  if (dbi) mdbx_dbi_close(env, dbi);
  if (env) mdbx_env_close(env);
  return (rc != MDBX_SUCCESS) ? EXIT_FAILURE : EXIT_SUCCESS;
}
