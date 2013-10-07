<?php


class ArrayIterator implements Iterator {
  private $var = array();

  public function __construct( $array ) {
    if( is_array( $array ) ) {
      $this->var = $array;
    }
  }
  public function rewind() {
    return reset( $this->var );
  }
  public function current() {
    return current( $this->var );
  }
  public function key() {
    return key( $this->var );
  }
  public function next() {
    next( $this->var );
  }
  public function valid() {
    return $this->current() !== false;
  }
}

?>