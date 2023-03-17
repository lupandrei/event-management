#include "validare.h"

void Validator::validateEvent(const Event& ev)
{
	string err = "";
	if (ev.get_id() < 0)
		err += "Invalid id\n";
	if (ev.get_title() == "")
		err += "Invalid title\n";
	if (ev.get_description() == "")
		err += "Invalid description\n";
	if (ev.get_type() == "")
		err += "Invalid type\n";
	if (ev.get_time() < 0)
		err += "Invalid time\n";
	if (err.size() > 0)
		throw ValidationException(err);
}
