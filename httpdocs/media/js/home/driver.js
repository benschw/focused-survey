var survey = false;
window.addEvent("domready",function(){
	AutoSize.initialize();
	
	new MBox( $('mainHelp'), {
		width  : 600,
		height : 400,
		title  : "Help"
	} );
	
	new LogoutButton( 'performLogout' );
	$('loadActiveSurveys').addEvent( 'click', function(e) {
		if( !survey || !survey.hasChanges() || confirm( "There are unsaved changes. Are you sure you want to leave this survey?" ) ) {

			var active = new ListComponent({ 
				'id' : 'active',
				'methods' : ['add'],
				'class' : 'Survey.AdminSurvey',
				loadTool : function(id) {
					survey = new Survey(id, { reloadList : function() { active.reload(); } });
				},
				hasChanges : function() {
					return survey && survey.hasChanges()
				}
			});
		}
	});
	
	$('loadCompleteSurveys').addEvent( 'click', function(e) {
		if( !survey || !survey.hasChanges() || confirm( "There are unsaved changes. Are you sure you want to leave this survey?" ) ) {
			var complete = new ListComponent({ 
				'id' : 'complete',
				'class' : 'Survey.AdminSurvey',
				loadTool : function(id) {
					survey = new Survey(id, { reloadList : function() { complete.reload(); } });
				},
				hasChanges : function() {
					return survey && survey.hasChanges()
				}
		 });
		}
	});

});