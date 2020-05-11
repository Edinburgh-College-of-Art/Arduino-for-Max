function anything()
{
	var inmsg = arrayfromargs(messagename, arguments);
	var outmsg = String(inmsg).split("/").slice(1)

	outmsg[outmsg.length-1] = outmsg[outmsg.length-1].split(",")
	var value = outmsg[outmsg.length-1].pop()

	outmsg[outmsg.length-1] = outmsg[outmsg.length-1].pop()
	outmsg.push(Number(value))

	outlet(0,outmsg);
}