var Survey = Class({
	selectedSurvey : null,
	_hasChanges : false,
	
	Implements: [Options, Events],
	options: {
		'id' : null,
		onReload : function(){}
	},
	initialize : function(id, options) {
		this.setOptions(options);
		this.selectedSurvey = id;
		this.reload();
	},
	hasChanges : function() {
		return this._hasChanges;
	},
	//==========================================================================
	// Load
	//==========================================================================
	reload : function() {
		var request = new Request.HTML({
			url: 'fw.Survey.AdminSurvey.load', 
			update: $('surveyToolsPanel'),
			onSuccess : function() {
				AutoSize.redraw();
				$('toolPanelForm').addEvent( 'change', function(e) {
					this._hasChanges = true;
				}.bind(this));
				$$('.instructionsHelp').each( function( handle ) {
					new MBox( handle, {
						width  : 600,
						height : 400,
						title  : handle.alt
					} );
				});
				
				$$("#surveyToolNav li").each( function( toolHandle ) {
					toolHandle.addEvent( 'click', function(e) {
						$('extraFunctions').innerHTML = '';
						
						$$("#surveyToolNav li").each( function( l ) {
							l.removeClass( 'selected' );
						});
						toolHandle.addClass( "selected" );
						$$(".toolPanel").each( function( toolPanel ) {
							toolPanel.addClass( 'hidden' );
						});
						$(toolHandle.id+"Panel").removeClass( "hidden" );
						if( toolHandle.id == 'admins' ) {
							var l = new Element( 'label', {'class' : 'note'});
							l.innerHTML = 'Add New Administrator';
							$('extraFunctions').appendChild( l );
							var inp = new Element( 'input', { 'id' : 'newAdmin' });
							$('extraFunctions').appendChild( inp );
							var myButton = new Element( "img", { 'id' : 'performAddAdministrator', 'alt' : 'Add Entry', 'src' : "/media/images/add-big.png" } );
							myButton.setStyle( 'cursor', 'pointer' );
							myButton.addEvent( 'click', function(e) {
								this.addAdmin();
							}.bind(this));
							$('extraFunctions').appendChild( myButton );
						}
						if( toolHandle.id == 'moderate' ) {
							var l = new Element( 'label', {'class' : 'note'});
							l.innerHTML = 'Add New Entry';
							$('extraFunctions').appendChild( l );
							var inp = new Element( 'input', { 'id' : 'newEntry' });
							$('extraFunctions').appendChild( inp );
							var myButton = new Element( "img", { 'id' : 'performAddEntry', 'alt' : 'Add Entry', 'src' : "/media/images/add-big.png" } );
							myButton.setStyle( 'cursor', 'pointer' );
							myButton.addEvent( 'click', function(e) {
								this.addEntry();
							}.bind(this));
							$('extraFunctions').appendChild( myButton );
						}
					}.bind(this));
				}.bind(this));
				this.setupTabs();
				$('saveSurvey').addEvent( 'click', function(e) {
					this.save();
				}.bind(this));
				this.options.reloadList();
			}.bind(this)
		}).get({ 'id' : this.selectedSurvey });
	},

	//==========================================================================
	// Initialize Tab Behavior
	//==========================================================================
	setupTabs : function() {
		this.setupSchedulingPanel();
		this.setupAdminPanel();
		this.setupModeratePanel();
	},
	setupSchedulingPanel : function() {
		myCal 	= new Calendar({ phase1: 'm/d/Y' });
		myCal2 	= new Calendar({ phase2: 'm/d/Y' });
		myCal3 	= new Calendar({ end: 'm/d/Y' });
		if( $("schedulingType") ) {
			this.performScheduleToggle();
			$$("#schedulingType input").each( function( mode ) {
				mode.addEvent( 'click', function(e) {
					this.performScheduleToggle();
				}.bind(this));
			}.bind(this));
		}
	},
	performScheduleToggle : function() {
		$$("#schedulingType input").each( function( option ) {
			if( option.checked ) {
				if( option.value == 'schedule' ) {
					$('scheduleMode').removeClass( 'hidden' );
					$('toggleMode').addClass( 'hidden' );
				}
				if( option.value == 'toggle' ) {
					$('toggleMode').removeClass( 'hidden' );
					$('scheduleMode').addClass( 'hidden' );
				}
			}
		});
	},
	setupAdminPanel : function() {
		if( $("adminsPanel") ) {
			var myTable = $$("#adminsPanel table")[0].getFirst("tbody");
			myTable.getElements('tr').each( function(row) {
				row.getElements('img')[row.getElements('img').length-1].addEvent( 'click', function(e) {
					row.destroy();
				});
			});
		}
	},
	addAdmin : function() {
		this._hasChanges = true;
	
		var myTable = $$("#adminsPanel table")[0].getFirst("tbody");
	
		var tpl = myTable.getLast("tr").clone();
		tpl.getElements('img')[tpl.getElements('img').length-1].addEvent( 'click', function(e) {
			tpl.destroy();
		});
		tpl.getElements("input").each( function( elem ) {
			elem.value = '';
			elem.checked = false;
		});
		tpl.getElement("input").value = $('newAdmin').value;
		myTable.appendChild( tpl );
	},
	setupModeratePanel : function() {
		if( $("moderatePanel") ) {
			var myTable = $$("#moderatePanel table")[0].getFirst("tbody");
			myTable.getElements('tr').each( function(row) {
				row.getElement('.delete').addEvent( 'click', function(e) {
					this._hasChanges = true;
					row.getElement('.delete').addClass( 'hidden' )
					row.getElement('.enable').removeClass( 'hidden' );
					row.addClass( 'deleted' );
				}.bind(this));
				row.getElement('.enable').addEvent( 'click', function(e) {
					this._hasChanges = true;
					row.getElement('.enable').addClass( 'hidden' )
					row.getElement('.delete').removeClass( 'hidden' );
					row.removeClass( 'deleted' );
				}.bind(this));
			}.bind(this));
		}
	},
	addEntry : function() {
		this._hasChanges = true;
		
		var myTable    = $$("#moderatePanel table")[0].getFirst("tbody");
		var tpl        = new Element('tr', { 'class' : 'new' });
		var cell       = new Element('td');
		cell.innerHTML = $('newEntry').value;
		tpl.appendChild( cell );
		var cell2      = new Element('td', { 'class' : 'deleteColumn'});
		var disable    = new Element( 'img', { 'class' : 'delete', 'alt' : 'Disable Entry', 'src' : "/media/images/remove.png" } );
		var enable     = new Element( 'img', { 'class' : 'enable hidden', 'alt' : 'Enable Entry', 'src'  : "/media/images/apply.png" } );
		disable.addEvent( 'click', function(e) {
			this._hasChanges = true;
			tpl.getElement('.delete').addClass( 'hidden' )
			tpl.getElement('.enable').removeClass( 'hidden' );
			tpl.addClass( 'deleted' );
		}.bind(this));
		enable.addEvent( 'click', function(e) {
			this._hasChanges = true;
			tpl.getElement('.enable').addClass( 'hidden' )
			tpl.getElement('.delete').removeClass( 'hidden' );
			tpl.removeClass( 'deleted' );
		}.bind(this));
		cell2.appendChild( disable );
		cell2.appendChild( enable );
		tpl.appendChild( cell2 );
		myTable.appendChild( tpl );
	
	},
	//==========================================================================
	// Save
	//==========================================================================
	save : function() {
		var data = {'id':this.selectedSurvey,general:{},schedule:{},admins:[],users:{},moderate:[]};
		if( $('generalPanel') ) {
			data.general['title']           = $('title').value;
			data.general.phase1Description  = $('phase1Description').value;
			data.general.phase1Subject      = $('phase1Subject').value;
			data.general.phase1Body         = $('phase1Body').value;
			data.general.phase2Description  = $('phase2Description').value;
			data.general.phase2Subject      = $('phase2Subject').value;
			data.general.phase2Body         = $('phase2Body').value;
		}
		if( $('schedulePanel') ) {
			if( $$("#schedulingType input[name=schedulingType]")[0].checked ) {
				data.schedule.schedulingType = $$("#schedulingType input[name=schedulingType]")[0].value;
			} else if( $$("#schedulingType input[name=schedulingType]")[1].checked ) {
				data.schedule.schedulingType = $$("#schedulingType input[name=schedulingType]")[1].value;
			}
			for( var i = 0; i < $$("#toggleMode input[name=toggleMode]").length; i++ ) {
				if( $$("#toggleMode input[name=toggleMode]")[i].checked ) {
					data.schedule.toggleMode = $$("#toggleMode input[name=toggleMode]")[i].value;
				}
			}
			data.schedule.phase1            = $('phase1').value;
			data.schedule.phase2            = $('phase2').value;
			data.schedule.end               = $('end').value;
		}
		if( $('adminsPanel') ) {
			$$("#adminsPanel table")[0].getElements("tr").each( function( user ) {
				if( user.getElements(".email]").length > 0 ) {
					data.admins.push({
								 	email                 : user.getElements(".email")[0].value,
								 	canModifyGeneral      : user.getElements(".canModifyGeneral")[0].checked,
								 	canSchedule           : user.getElements(".canSchedule")[0].checked,
								 	canManageAdmins       : user.getElements(".canManageAdmins")[0].checked,
								 	canManageParticipants : user.getElements(".canManageParticipants")[0].checked,
								 	canModerate           : user.getElements(".canModerate")[0].checked,
								 	canViewReports        : user.getElements(".canViewReports")[0].checked
					});
				}
			});
		}
		if( $('usersPanel') ) {
			data.users = $("participantsList").value;
		}
		if( $('moderatePanel') ) {
			$$("#moderatePanel table")[0].getElements("tr").each( function( entry ) {
				if( entry.getElement("td").value != '' ) {
					var isDeleted = entry.hasClass( 'deleted' );
					entry.removeClass( 'deleted' );
					var id = entry.className;
					data.moderate.push({
					 				'id'        : id,
								 	'entry'     : entry.getElements("td")[0].innerHTML,
								 	'isDeleted' : isDeleted
					});
				}
			});
		}
		if( $('reportsPanel') ) {
		
		}
		var request = new Request.JSON({
			'url'  : 'fw.Survey.AdminSurvey.save', 
			'data' : data,
			onSuccess: function( response ) {
				if( response.result ) {
					if( response.errors ) {
						alert( response.message );
					}
					this._hasChanges = false;
					this.reload();
				} else {
					alert( response.message );
				}
			}.bind(this)
		}).send();
		// alert( JSON.encode( data.moderate ) );
	}
	
});