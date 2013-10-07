<h2><tal:block content="data/title" /></h2>

<ul id="surveyToolNav">
	<li tal:repeat="tool data/tabs" tal:attributes="id tool/id; class tool/class | null">
		<a href="#" tal:content="tool/name" />
	</li>
</ul>
<div id="surveyToolsInnerWrapper">

	<form id="toolPanelForm">
		<div tal:repeat="tool data/tabs" tal:attributes="id tool/panelID; class tool/panelClass">
		 	<metal:block use-macro="survey.tools.tpl/${tool/panelID}" />
		</div>
	</form>

</div>
<div id="extraFunctions" />
<button id="saveSurvey">Save</button>
<div class="clear"></div>





<metal:block define-macro="generalPanel">
<a href="/fw.Survey.AdminSurvey.getHelp?type=general" class="instructionsHelp">
	<img alt="General" src="/media/images/help.png" /> 
</a>
	<div class="inner">
		<fieldset>
			Unique Survey Url: <a tal:attributes="href data/url" tal:content="data/url" />
		</fieldset>
		<hr />
		<fieldset>
			<label>Survey Title</label><br />
			<input type="text" id="title" tal:attributes="value data/title" /><br />
		</fieldset>
		<hr />
		<fieldset>
			<h3>Phase1 Preferences</h3>
			<label>Description <span class="note">(description/instructions for participants)</span></label><br />
			<textarea id="phase1Description" tal:content="data/phase1Description" /><br />
			<label>Email Subject</label><br />
			<input type="text" id="phase1Subject" tal:attributes="value data/phase1Subject" /><br />
			<label>Email Body</label><br />
			<textarea id="phase1Body" tal:content="data/phase1Body" />
		</fieldset>
		<hr />
		<fieldset>
			<h3>Phase2 Preferences</h3>
			<label>Description <span class="note">(description/instructions for participants)</span></label><br />
			<textarea id="phase2Description" tal:content="data/phase2Description" /><br />
			<label>Email Subject</label><br />
			<input type="text" id="phase2Subject" tal:attributes="value data/phase2Subject" /><br />
			<label>Email Body</label><br />
			<textarea id="phase2Body" tal:content="data/phase2Body" />
		</fieldset>
	</div>
</metal:block>

<metal:block define-macro="schedulePanel">
<a href="/fw.Survey.AdminSurvey.getHelp?type=schedule" class="instructionsHelp">
	<img alt="Schedule" src="/media/images/help.png" /> 
</a>
	<div id="schedulingType">
		<input type="radio" name="schedulingType" value="toggle" tal:attributes="checked data/isToggled"/>
		<label>Toggle Survey <span class="note">(set the phase)</span></label><br />
		<input type="radio" name="schedulingType" value="schedule" tal:attributes="checked data/isScheduled" />
		<label>Schedule Survey <span class="note">(set date ranges)</span></label>
	</div>
	<fieldset id="scheduleMode" class="hidden">
		<legend>Schedule My Survey</legend>
		<label for="phase1">Phase 1 Start Date <span class="note">(at midnight EST)</span></label>
		<input id="phase1" name="phase1" type="text" tal:attributes="value data/phase1Start" /><br />
		<label for="phase2">Phase 2 Start Date <span class="note">(at midnight EST)</span></label>
		<input id="phase2" name="phase2" type="text" tal:attributes="value data/phase2Start" /><br />
		<label for="end">End Date <span class="note">(at midnight EST)</span></label>
		<input id="end" name="end" type="text" tal:attributes="value data/end" /><br />
	</fieldset>
	<fieldset id="toggleMode" class="hidden">
		<h3>Toggle My Survey</h3>
		<input type="radio" name="toggleMode" value="new" tal:attributes="checked data/toggle/isNew" />
		<label>Not Started</label><br />
		<input type="radio" name="toggleMode" value="phase1" tal:attributes="checked data/toggle/isPhase1" />
		<label>Begin Phase 1</label><br />
		<input type="radio" name="toggleMode" value="phase2" tal:attributes="checked data/toggle/isPhase2" />
		<label>Begin Phase 2</label><br />
		<input type="radio" name="toggleMode" value="complete" tal:attributes="checked data/toggle/isComplete" />
		<label>Complete Survey</label><br />
	</fieldset>
</metal:block>

<metal:block define-macro="adminsPanel">

	<fieldset>
		<a href="/fw.Survey.AdminSurvey.getHelp?type=admins" class="instructionsHelp">
			<img alt="Admins" src="/media/images/help.png" /> 
		</a>
		<table>
			<thead>
				<tr>
					<th rowspan="2">Email</th>
					<th colspan="6">Permissions <span class="note">(check to give permission to use these tabs)</span></th>
					<th rowspan="2">Delete</th>
				</tr>
				<tr><th>General</th><th>Schedule</th><th>Admins</th><th>Users</th><th>Moderate</th><th>Reports</th></tr>
			</thead>
			<tbody>
				<tr tal:repeat="user data/administrators">
					<td><input class="email" type="text" tal:attributes="value user/email" /></td>
					<td><input class="canModifyGeneral" type="checkbox" tal:attributes="checked user/canModifyGeneral" /></td>
					<td><input class="canSchedule" type="checkbox" tal:attributes="checked user/canSchedule" /></td>
					<td><input class="canManageAdmins" type="checkbox" tal:attributes="checked user/canManageAdmins" /></td>
					<td><input class="canManageParticipants" type="checkbox" tal:attributes="checked user/canManageParticipants" /></td>
					<td><input class="canModerate" type="checkbox" tal:attributes="checked user/canModerate" /></td>
					<td><input class="canViewReports" type="checkbox" tal:attributes="checked user/canViewReports" /></td>	
					<td><img alt="Delete Administrator" src="/media/images/delete-user.png" /></td>
				</tr>
			</tbody>
		</table>
		<div class="clear"></div>
	</fieldset>
	
</metal:block>

<metal:block define-macro="usersPanel">
<a href="/fw.Survey.AdminSurvey.getHelp?type=users" class="instructionsHelp">
	<img alt="Users" src="/media/images/help.png" /> 
</a>
	<fieldset>
		<label>List Participants <span class="note">(comma delimited)</span></label><br />
		<textarea id="participantsList" tal:content="data/participants" />
	</fieldset>
</metal:block>

<metal:block define-macro="moderatePanel">
<a href="/fw.Survey.AdminSurvey.getHelp?type=moderate" class="instructionsHelp">
	<img alt="Moderate" src="/media/images/help.png" /> 
</a>
	<fieldset>
		<table>
			<tbody>
				<tr tal:repeat="entry data/entries" tal:attributes="class entry/class | null">
					<td tal:content="entry/content" />
					<td class="deleteColumn">
						<img tal:condition="entry/isDeleted" class="delete hidden" alt="Delete Entry" src="/media/images/remove.png" />
						<img tal:condition="not: entry/isDeleted" class="delete" alt="Delete Entry" src="/media/images/remove.png" />

						<img tal:condition="entry/isDeleted" class="enable" alt="Enable Entry" src="/media/images/apply.png" />
						<img tal:condition="not: entry/isDeleted" class="enable hidden" alt="Delete Entry" src="/media/images/apply.png" />
					</td>
				</tr>
			</tbody>
		</table>
		<div class="clear"></div>
	</fieldset>
</metal:block>

<metal:block define-macro="reportsPanel">
<a href="/fw.Survey.AdminSurvey.getHelp?type=users" class="instructionsHelp">
	<img alt="Users" src="/media/images/help.png" /> 
</a>
	<fieldset>
		<a href="download-csv/${data/id}">download</a>
		<p class="note">Ratings are on a scale of -50 (strongly disagree) to 50 (strongly agree).</p>
		<p class="note">There were <em tal:content="data/timesRated" /> Participants in Phase II</p>
		<table>
			<thead>
				<tr><th>Avg. Rating</th><th>Med. Rating</th><th>No Opinion</th><th>Entry</th></tr>
			</thead>
			<tbody>
				<tr tal:repeat="entry data/reports" tal:attributes="class entry/class | null">
					<td class="rating" tal:content="entry/average" />
					<td class="rating" tal:content="entry/median" />
					<td class="rating" tal:content="entry/noOpinion" />
					<td tal:content="entry/content" />
				</tr>
			</tbody>
		</table>
	</fieldset>
</metal:block>
