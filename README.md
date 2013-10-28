## Focused Survey

Collaborative survey application where instead of the person conducting the survey driving its direction, the participants do.

## Install
- update config/config.ini with database connection settings
- import db.sql into the same database
- host `httpdocs` someplace
- curl http://_yourdomain.com_/cron nightly (whenever you want the emails to go out and the phases to cut over)


## notes

### mailer
emails are sent using php's `mail()` function. On *nix, this invokes the sendmail binary, which then uses the mail configuration to route the email. On Windows, it sends to a SMTP server. In both cases the sysadmin sets up the mail system


### db setup
	CREATE DATABASE focused_survey;
	CREATE USER 'focused'@'localhost' IDENTIFIED BY 'changeme';
	GRANT SELECT, INSERT, UPDATE ON focused_survey.* TO 'focused'@'localhost';
	mysql -u root -p -h localhost focused_survey < db.sql


## OS

sudo aptitude install mysql-server apache2 php5 php5-mysql

sudo a2enmod rewrite