#include "test_helper.h"

extern string database_file;

class BaseAttributeTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    Person::setup( NULL );
  }
};

TEST_F( BaseAttributeTest, Defaults ) {
  Person joe;

  ASSERT_EQ( -1, joe.integer( "id" ) );
}

TEST_F( BaseAttributeTest, SettingAttributesSingly ) {
  Person joe;
  joe[ "name" ]    = "Joe";
  joe[ "surname" ] = "Yates";
  joe[ "age" ]     = 45;
  joe[ "height" ]  = 1.80;

  assert_string( "Joe", joe.text( "name" ) );
  ASSERT_EQ( 45, joe.integer( "age" ) );
  ASSERT_DOUBLE_EQ( 1.80, joe.floating_point( "height" ) );
}

TEST_F( BaseAttributeTest, SettingAttributesUsingAttributesMethod ) {
  Person joe( attributes
              ( "name", "Joe" )
              ( "surname", "Yates" )
              ( "age", 45 )
              ( "height", 1.80 ) );

  assert_string( "Joe", joe.text( "name" ) );
  ASSERT_EQ( 45, joe.integer( "age" ) );
  ASSERT_DOUBLE_EQ( 1.80, joe.floating_point( "height" ) );
}

class BaseSaveTest : public ::testing::Test {
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

TEST_F( BaseSaveTest, Save ) {
  Person joe;
  joe[ "name" ]    = "Joe";

  ASSERT_TRUE( joe.save() );
  ASSERT_TRUE( joe.integer( "id" ) > 0 );
}

TEST_F( BaseSaveTest, SaveWithNoData ) {
  Person joe;

  ASSERT_TRUE( joe.save() );
  ASSERT_TRUE( joe.integer( "id" ) > 0 );
}