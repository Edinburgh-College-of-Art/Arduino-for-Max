# Arduino to Max via OSC

For the most part these examples will use the [OSC library by Adrian Freed and Yotam Mann](https://github.com/CNMAT/OSC)

## Parsing OSC Messages

To parse OSC messages you can use the OSC Route also provided by CNMAT. This can be installed either through [Max's package manager](https://docs.cycling74.com/max8/vignettes/package_manager?q=package) or you can [download a release directly from the repository](https://github.com/CNMAT/CNMAT-odot/releases).

You could also implement your own solutions for parsing OSC messages. A cheap and nasty way by using [Max's `js` object](https://docs.cycling74.com/max8/refpages/js?q=js) can be achieved with the following script and the [`route` object](https://docs.cycling74.com/max8/refpages/route?q=route)

```js
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
```

A test example is provided here:

```
----------begin_max5_patcher----------
888.3ocyWsrbZCCEcM7UnQqfYbH9MP6zE4CncSWFxjQXDDkwVxijLkzL4euR
WYSfTvwDnYJKvijtONmqO5J4m62COWrgpvnuftE0q2y860ClxNQu5w8vEjMY
4DEXFNSTTP4ZrmaMMciFl+lEKP5GXJjVfdTgDyejloQpLIqbqwkDc1CL9p6k
l0bIMcjuGJD9KNFdLdjO5tZGVJ35kjLp01f543UELdNUq1cR1B.DlrdUBdGm
Ure6bdhI1a8WToaBfucxW5229m2YVBVVwyzLAGQ3Oos7bvvY7mmwmoWSjHFu
PsB8MDQJIOsTJJHxUpAETkhrhxIETOyRqprQVM7qMdYfpysepk1HBQY3HUYN
SOXF95YXyfbVFcPfIYVubdbq6wnbJek9gqBtyDhirx1f4YBVSdWSxqns3Son
bvGNgMNW65nxJ0CC9QUwbpb.j3guFZyKpA9dNCskkWZJ64LNMSTwgZePz6Hw
hBr+Gm5CZL+fcDYumfJBeXkyNxL6qOv9uK3jLA9CHp3.8aYmRhu+nDC1CBsO
RbDI7D3QP5qQWZ.rlJu2H7lmS2kN6Sxv5YcSoepj5.CF6gvyI7UXzceDxR+k
AQ+0FHoIMTT8Vh2uTDLN09XZb6khvCTJ7wmNc+GPUgJqCzLFdjFdxzbx+GrT
SU5NPy.GMiN82leZz7MRys77ZKEu17175ZKPA9Sagxwicsi.dGM8zYb3gobv
Qo7EktlC.KY4ssCM0nVSlDEEEL08KbRMcSR.1FcJrcxAORO5HGo2VQ3P8ruQ
xH43Kmn2d6GU1UllrJ5nGUuuLHcJzFKr8Byg5nO8SnvTuhhrlt3d205tmnM2
FYtYuspt7TWeLAvnK1FfCTFNxgOvZP4+RoQEkTdaBTnJ4jjw9mrjLJ7yURBl
AW44MWVGnlc98KQJQkLqIIM6gPuxuEl9ULNwda0cMZ5dFUvVTJXbccJSGaTn
ucOcBb3a7Dn2scvQZzzUbZKrmKNCCa.ykDYAmOxpAi8Sb71cv4hrocAYc.XA
9Py4j.XCAL5bgVGP1j1PVCVh1CYQmOx5z9A+t.sz8fV5Enn42Erk1ArAeni2
di1Cat1Jjxx0TopN9.rL8XeTHsCm3ACYb2PnSFVRWyZrG9xKLQZ5vpMsWqjt
VXaRiwNWEKnRdEC7tusfXRIz+11tSUV+48Pa99uz+OvmbMfP
-----------end_max5_patcher-----------
```
