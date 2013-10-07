<?php

class MysqlIterator implements Iterator {

  private $results      = null;
  private $index        = 0;
  private $numRows      = 0;
  private $errors       = array();

  public function __construct( $results ) {
    if( is_resource( $results ) && 
        get_resource_type( $results ) == "mysql result" ) {
      $this->results = $results;
      $this->numRows = mysql_num_rows( $this->results );
    } else {
      throw new Exception( "Expected MySQL Result" );
    }
  }

  public function rewind() {
    $this->index = 0;
  }

  public function current() {
    $this->goto( $this->index );
    return mysql_fetch_assoc( $this->results );
  }

  public function key() {
    return $this->index;
  }

  public function next() {
    $this->index++;
  }

  public function valid() {
    return $this->index < $this->numRows;
  }

  private function goto( $index ){
    return mysql_data_seek( $this->results, $index );
  }

}

?>