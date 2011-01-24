#include "test_helper.h"

template <>
string ActiveRecord::Base<Person>::class_name = "Person";

ActiveRecord::Connection connection;
string database_file = "./test.sqlite3";

void delete_database() {
  string remove_database = "rm -f " + database_file;
  system( remove_database.c_str() );
}

void connect_database() {
  connection.connect( options
                     ( "adapter", "sqlite" )
                     ( "database", database_file ) );
}

void assert_field_name( const TableData &td, int field_index, const string &name ) {
  ASSERT_STREQ( td.fields[ field_index ].name().c_str(), name.c_str() );
}
