<?php

class Tree {
  
  protected $tree_id = -1;
  protected $tree_parentID;
  protected $data;
  protected $children;

  public function __construct( $data = null ) {
    $this->data = $data;
    $this->children = array();
    if( !is_null( $data ) ) {
      $this->tree_id = $data->getID();
      $this->tree_parentID = $data->getParentID();
    }
  }

  public static function build( $dataArr, $rootParent = -1 ) {
    $root = new Tree();
    $root->setID( $rootParent );
    $root->tree_arrangeBranches( $dataArr );
    return $root;
  }

	//==========================================================================
  public function setID( $id ) {
    $this->tree_id = $id;
  }
  public function getID() {
    return $this->tree_id;
  }
  public function getParentID() {
    return $this->tree_parentID;
  }
	public function getChildren() {
		return $this->children;
	}
	public function getRootNode() {
		return $this->data;
	}
	
  public function __call( $method, $args = array() ) {
    $result = null;
    if( !is_null( $this->data ) ) {
      $result = $this->data->{$method}( $args );
    }

    $childData = array();
    foreach( $this->children AS $child ) {
      $childData[] = $child->__call( $method, $args );
    }

    return array( 'data'      => $result,
                  'children'  => $childData 
                );
  }

	public function sort( $method, $order = 'ASC' ) {
		$hash 	= array();
		foreach( $this->children AS $child ) {
			$hash[ $child->data->{$method}() ] = $child;
		}
		if( $order == 'DESC' ) {
			$sorted = krsort( $hash );
		} else {
			$sorted = ksort( $hash );
		}
		$this->children = array_values( $hash );
		
		foreach( $this->children AS $child ) {
      $child->sort( $method, $order );
    }
    
	}

	//==========================================================================
  protected function tree_arrangeBranches( $dataArr ) {

    foreach( $dataArr AS $node ) {

      if( $node->getParentID() == $this->getID() ) {
        $this->children[] = new Tree( $node );
      }
    }

    foreach( $this->children AS $child ) {
      $child->tree_arrangeBranches( $dataArr );
    }
  
  }

}

?>