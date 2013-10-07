<?php

abstract class ActiveRecord {

  protected $id = null;
  protected $table;
  protected $properties = array();
  
  public function __construct( $id, $table ) {
    $this->id     = $id;
    $this->table  = $table;

    if( !is_null( $this->id ) ) {
      $id = Utilities::mysqlEscape( $this->id );
      $db = Mysql::singleton();
      $props = $db->selectRecord( "SELECT * FROM `{$table}` WHERE id = '{$id}'" );
      foreach( $props AS $key => $val ) {
        if( $key != 'id' ) {
          $this->setActiveProperty( $key, $val );
        }
      }
    }
  }
  
  protected function setActiveProperty( $key, $val ) {
    return $this->properties[$key] = $val;
  }
  protected function getActiveProperty( $key ) {
    return $this->properties[$key];
  }
  protected function isActivePropertySet( $key ) {
    return isset( $this->properties[$key] );
  }
  protected function unsetActiveProperty( $key ) {
    unset( $this->properties[$key] );
  }
  
  public function save() {
    if( is_null( $this->id ) ) {
      return $this->insert();
    } else {
      return $this->update();
    }
  }
  
  protected function update() {
    if( count( $this->properties ) > 0 ) {
      $sql = array();
      foreach( $this->properties AS $key => $val ) {
        $key = Utilities::mysqlEscape( $key );
        $val = Utilities::mysqlEscape( $val );
        $sql[] = "`{$key}` = '{$val}'";
      }
      $sqlStr = implode( ", ", $sql );
    
      $db = Mysql::singleton();
      return $db->update( "UPDATE `{$this->table}` SET {$sqlStr} WHERE id = '{$this->id}'" );
    } else {
      return true;
    }
  }
  protected function insert() {
    if( count( $this->properties ) > 0 ) {
      $keys = array();
      $vals = array();
      foreach( $this->properties AS $key => $val ) {
        $key = Utilities::mysqlEscape( $key );
        $val = Utilities::mysqlEscape( $val );
        $keys[] = "`{$key}`";
        $vals[] = "'{$val}'";
      }
      $set    = implode( ", ", $keys );
      $values = implode( ", ", $vals );

      $db = Mysql::singleton();
      return $db->insert( "INSERT INTO `{$this->table}` ( {$set} ) VALUES ( {$values} )" );
    } else {
      return true;
    }
  }
}

?>