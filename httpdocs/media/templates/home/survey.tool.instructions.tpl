<h2></h2>
<div id="surveyToolsOverview" class="instructions">
	<div class="verbose">
		<metal:block use-macro="survey.tool.instructions.tpl/${data/type}" />
	</div>
</div>


<metal:block define-macro="empty">
	<p>Please Select a survey from the left to continue.</p>
	<p>
		Depending on the survey's current status (active, complete, etc.) 
		and your permissions (the ability to schedule, moderate, 
		view results etc.) for each survey, the management tools may differ.
	</p>
</metal:block>


<metal:block define-macro="active">
	<ul>
		<li>To start a new survey, select <img alt="add" src="/media/images/add-big.png" /> from the bottom left of the list on the left.</li>
		<li>Select the survey you just created, one you are coming back to, or one you were invited to administer.</li>
	</ul>
	<p>Depending on your permissions for the selected survey, and the survey's current state, you may have access to edit:</p>
	<dl>
		<metal:block use-macro="survey.tool.instructions.tpl/general" />
		<metal:block use-macro="survey.tool.instructions.tpl/schedule" />
		<metal:block use-macro="survey.tool.instructions.tpl/admins" />
		<metal:block use-macro="survey.tool.instructions.tpl/moderate" />
		<metal:block use-macro="survey.tool.instructions.tpl/users" />
	</dl>
</metal:block>

<metal:block define-macro="complete">
	<p>Select a completed survey from the left to view it's details.</p>
	<p>Depending on your permissions for the selected survey, and the survey's current state, you may have access to edit:</p>
	<dl>
		<metal:block use-macro="survey.tool.instructions.tpl/general" />
		<metal:block use-macro="survey.tool.instructions.tpl/schedule" />
		<metal:block use-macro="survey.tool.instructions.tpl/admins" />
		<metal:block use-macro="survey.tool.instructions.tpl/reports" />
	</dl>
</metal:block>


<metal:block define-macro="general">
	<dt>General</dt>
	<dd>
		Edit the survey name, topic description, etc. 
		<a href="/fw.Survey.AdminSurvey.getHelp?type=general" class="instructionsHelp">
			<img alt="General" src="/media/images/help.png" /> 
		</a>
	</dd>
</metal:block>
<metal:block define-macro="schedule">
	<dt>Schedule</dt>
	<dd>
		Either schedule the phases of your survey, or toggle between them immediately.
		<a href="/fw.Survey.AdminSurvey.getHelp?type=schedule" class="instructionsHelp">
			<img alt="Schedule" src="/media/images/help.png" /> 
		</a>
	</dd>
</metal:block>
<metal:block define-macro="admins">
	<dt>Admins</dt>
	<dd>
		Add other administrators to your survey.
		<a href="/fw.Survey.AdminSurvey.getHelp?type=admins" class="instructionsHelp">
			<img alt="Admins" src="/media/images/help.png" /> 
		</a>
	</dd>
</metal:block>
<metal:block define-macro="moderate">
	<dt>Moderate</dt>
	<dd>
		Add extra entries to your survey, or delete one submitted by a participant.
		<a href="/fw.Survey.AdminSurvey.getHelp?type=moderate" class="instructionsHelp">
			<img alt="Moderate" src="/media/images/help.png" /> 
		</a>
	</dd>
</metal:block>
<metal:block define-macro="users">
	<dt>Users</dt>
	<dd>
		Manage the list of participants who will get notification emails when your survey starts and shifts between phases.
		<a href="/fw.Survey.AdminSurvey.getHelp?type=users" class="instructionsHelp">
			<img alt="Users" src="/media/images/help.png" /> 
		</a>
	</dd>
</metal:block>
<metal:block define-macro="reports">
	<dt>Reports</dt>
	<dd>
		View the reponse to your survey.
		<a href="/fw.Survey.AdminSurvey.getHelp?type=users" class="instructionsHelp">
			<img alt="Users" src="/media/images/help.png" /> 
		</a>
	</dd>
</metal:block>
