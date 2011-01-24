#include "test_helper.h"

extern ActiveRecord::Connection connection;
extern string database_file;

class SchemaTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    delete_database();
    string create = "echo 'CREATE TABLE foo (bar INTEGER, baz TEXT, qux REAL);' | sqlite3 " + database_file + ";";
    system( create.c_str() );
    connect_database();
  }
  virtual void TearDown() {
    delete_database();
  }
};

TEST_F( SchemaTest, LoadsSchema ) {
  Schema schema       = connection.schema();
  TableData foo_table = schema[ "foo" ];
  ASSERT_EQ( foo_table.fields.size(), 3 );
  assert_field_name( foo_table, 0, "bar" );
  assert_field_name( foo_table, 1, "baz" );
  assert_field_name( foo_table, 2, "qux" );
}
