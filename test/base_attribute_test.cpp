#include "test_helper.h"

extern string database_file;

class BaseAttributeTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    delete_database();
    connect_database( connection, database_file );
    Person::setup( &connection );
    ActiveRecord::tables.update_database();
  }
  virtual void TearDown() {
    delete_database();
  }
 protected:
  Connection connection;
};

TEST_F( BaseAttributeTest, SetSingly ) {
  Person joe;
  joe[ "name" ]    = "Joe";
  joe[ "surname" ] = "Yates";
  joe[ "age" ]     = 45;
  joe[ "height" ]  = 1.80;

  ASSERT_EQ( -1, joe.integer( "id" ) );
  EXPECT_TRUE( joe.save() );
  ASSERT_GT( 0, joe.integer( "id" ) );
}
