## Focused Survey

Collaborative survey application where instead of the person conducting the survey driving its direction, the participants do.

## Install
- update config/config.ini with database connection settings
- import db.sql into the same database
- host `httpdocs` someplace
- curl http://_yourdomain.com_/cron nightly (whenever you want the emails to go out and the phases to cut over)
