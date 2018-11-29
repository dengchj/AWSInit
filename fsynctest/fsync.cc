#include <rados/librgw.h>
#include <rados/rgw_file.h>
#include <string>
#include <iostream>
#include <ctime>
#include <assert.h>

using namespace std;

int create_file(struct rgw_fs *fs, struct rgw_file_handle *bucket_fh,
                const char *name, struct stat *st, uint32_t mask,
                struct rgw_file_handle *obj_fh, uint32_t posix_flags,
                uint32_t flags)
{
  int rc = 0;
  //rc = rgw_create(fs, bucket_fh, name, &st, mask,
    //  &obj_fh, 0 /* posix flags */, RGW_CREATE_FLAG_NONE);
  cout<<"rgw_create rc="<<rc<<endl;
  return rc;
}

int mkdir()
{
  int rc = 0;

  return rc;
}

int test_librgw(bool is_file, size_t num_write)
{
  /* Return code */
  int rc = 0;
  /* Return code from RGW calls */
  int rgw_status;

  librgw_t rgw_handle = nullptr;
  string uid("user1");
  string access_key("user1");
  string secret_key("user1");
  struct rgw_fs *fs = nullptr;
  int argc = 3;
  char *argv[5] = {
      "nfs-ganesha", "--conf=/dist/UMStor-OS/build/ceph.conf", "--name=client.librgw", NULL, NULL };
  uint32_t create_mask = RGW_SETATTR_UID | RGW_SETATTR_GID | RGW_SETATTR_MODE;

  rc = librgw_create(&rgw_handle, argc, argv);
  cout<<"librgw_create rc="<<rc<<endl;

  rc = rgw_mount(rgw_handle,
      uid.c_str(),
      access_key.c_str(),
      secret_key.c_str(),
      &fs,
      RGW_MOUNT_FLAG_NONE);

  cout<<"rgwmount rc="<<rc<<endl;

  struct rgw_file_handle* root_fh = fs->root_fh;
  struct rgw_file_handle* bucket_fh = nullptr;
  struct rgw_file_handle* obj_fh = nullptr;
  string bucket = "test";
  string dir = "testdir3";

  time_t now = time(0);
  tm* gmt;
  char buf[128]={0};
  gmt = gmtime(&now);
  strftime(buf, 64, "%Y%m%d%H%M%S", gmt);
  string obj = buf;
  obj += ".d";
  struct stat st;

  st.st_uid = 0;
  st.st_gid = 0;
  st.st_mode = 644;

  rc = rgw_lookup(fs, root_fh, bucket.c_str(), &bucket_fh, RGW_LOOKUP_FLAG_NONE);
  cout<<"rgw_lookup rc="<<rc<<endl;

  if (is_file)
  {
    rc = rgw_create(fs, bucket_fh, obj.c_str(), &st, create_mask,
        &obj_fh, 0 /* posix flags */, RGW_OPEN_FLAG_V3 );
     cout<<"rgw_create rc="<<rc<<endl;

    /* open handle */
    //rc = rgw_open(fs, obj_fh, 0 /* posix flags */, 0 /* flags */);
    //cout<<"rgw_open rc="<<rc<<endl;
    /* stage seq write */
    size_t num = num_write;
    size_t offset = 0;
    size_t nbytes;
    //string data = "data for " + obj;
    void *data = new char[5194304];
    for (size_t i = 0; i < num ; i++)
    {
      //data += to_string(i);
      cout<<"offset:"<<offset<<"\n";
      rc = rgw_write(fs, obj_fh, offset, 5194304, &nbytes,
      (void*) data, RGW_OPEN_FLAG_V3);
      cout<<"rgw_write rc="<<rc<<endl;
      cout<<"nbytes:"<<nbytes<<"\n";

      rc = rgw_fsync(fs, obj_fh, 0);
      offset += nbytes;
    }
  }
  else
  {
     rc = rgw_mkdir(fs, bucket_fh, dir.c_str(), &st, create_mask,
         &obj_fh, RGW_MKDIR_FLAG_NONE);
     cout<<"rgw_mkdir rc="<<rc<<endl;
  }

  librgw_shutdown(rgw_handle);

  return rc;

}

void fsync()
{

}

int main()
{
  bool is_file = true;
  test_librgw(is_file,2);
  return 0;
}
