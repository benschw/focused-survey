var ListComponent = new Class({
	Implements: [Options, Events],
	options: {
		'class'    : '',
		'id'       : null,
		'methods'  : [],
		loadTool   : function(){},
		hasChanges : function() { return false; }
	},
	initialize : function(options) {
		this.setOptions(options);
		this.initListPanel( this.options.id );
	},
	hasChanges : function() {
		return this.options.hasChanges();
	},
	// ==========================================================================
	// Load
	// ==========================================================================
	initListPanel : function( type ) {
		this.options.id = type;
		var request = new Request.HTML({
			'url': 'fw.'+this.options['class']+'.loadList', 
			'update': $('panel'),
			'onSuccess' : function() {
				AutoSize.redraw();
				this.loadInstructions();
			}.bind(this)
		}).get();
	},
	loadInstructions : function() {
		var request = new Request.HTML({
			'url': 'fw.'+this.options['class']+'.loadInstructions', 
			'update': $('surveyToolsPanel'),
			onSuccess : function() {
				AutoSize.redraw();
				this.reload();
				$$('.instructionsHelp').each( function( handle ) {
					new MBox( handle, {
						'width'  : 600,
						'height' : 400,
						'title'  : handle.alt
					} );
				});
				
			}.bind(this)
		}).get({ 'id' : this.options.id });
	},
	reload : function() {
		var request = new Request.HTML({
			'url': 'fw.'+this.options['class']+'.loadList', 
			'update': $('listComponentWrapper'),
			onSuccess : function() {
				AutoSize.redraw();
				if( this.options.methods.contains( 'add' ) ) {
					var addButton = new Element( "img", { 'src' : '/media/images/add-big.png', 'alt' : 'Add' } );
					addButton.addEvent( 'click', function(e) {
						this.add();
					}.bind(this));
					addButton.inject( 'listComponentTools' );
				}
				if( this.options.methods.contains( 'delete' ) ) {
					var addButton = new Element( "img", { 'src' : '/media/images/remove.png', 'alt' : 'Delete' } );
					addButton.addEvent( 'click', function(e) {
						this.remove();
					}.bind(this));
					addButton.inject( 'listComponentTools' );
				}
				$$( "#listComponent li" ).each( function( sel ) {
					sel.addEvent( 'click', function(e) {
						this.loadTool( sel );
					}.bind(this));
					if( sel.id == this.selectedID ) {
						sel.addClass( 'selected' );
					}
				}.bind(this));
			}.bind(this)
		}).get({ 'id' : this.options['id'] });
	},
	loadRenameForm : function( elem ) {
		// Close Other Rename Forms, show new one
		$$("#listComponent li").each( function( li ) {
			if( !li.getElements( "span" )[0].hasClass( 'hidden' ) ) {
				li.getElements( "img.performCancel" )[0].fireEvent( 'click', li );
			}
		});
		elem.getElements( ".activateRenameForm" )[0].addClass( "hidden" );
		elem.getElements( "span" )[0].removeClass( "hidden" );	
		elem.getElements( "span input" )[0].focus();
		elem.getElements( "span input" )[0].addEvent( 'click', function(e) {
			new Event(e).stop();
		}.bind(this));
		
		// Rename
		elem.getElements( "img.performRename" )[0].addEvent( 'click', function(e) {
			new Event(e).stop();
			var listItem = elem.getElements( "img.performRename" )[0].getParent( 'li' );
			var id       = listItem.id;
			var newName  = listItem.getElements( "input" )[0].value;
			this.rename( id, newName );
		}.bind(this));
	
		// Cancel
		elem.getElements( "img.performCancel" )[0].addEvent( 'click', function(e) {
			new Event(e).stop();
			elem.getElements( ".activateRenameForm" )[0].removeClass( "hidden" );
			elem.getElements( "span" )[0].addClass( "hidden" );	
		}.bind(this));
	},
	
	//==========================================================================
	// Actions
	//==========================================================================
	loadTool : function( selected ) {
		if( this.hasChanges() ) {
			if( !confirm( "There are unsaved changes. Are you sure you want to leave this survey?" ) ) {
				return;
			}
		}
		
		this.selectedID = selected.id;
		$$( "#listComponent li.selected" ).each( function( elem ) {
			elem.removeClass( 'selected' );
		}.bind(this));
		selected.addClass( 'selected' );
		this.options.loadTool( selected.id );
	},
	
	add : function() {
		var request = new Request.JSON({
			'url': 'fw.'+this.options['class']+'.add', 
			onSuccess: function( response ) {				
				if( response.result ) {
					this.reload();
				} else {
					alert( response.message );
				}
			}.bind(this)
		}).send();
	},
	remove : function() {
		var request = new Request.JSON({
			'url': 'fw.'+this.options['class']+'.delete', 
			onSuccess: function( response ) {				
				if( response.result ) {
					this.reload();
				} else {
					alert( response.message );
				}
			}.bind(this)
		}).send();
	},
	
	rename : function( id, newName ) {
		var request = new Request.JSON({
			'url': 'fw.'+this.options['class']+'.rename', 
			'data' : { 'id' : id, 'newName' : newName },
			onSuccess: function( response ) {
				if( response.result ) {
					this.reload();
				} else {
					alert( response.message );
					this.reload();
				}
			}.bind(this)
		}).send();
	}
		
});
