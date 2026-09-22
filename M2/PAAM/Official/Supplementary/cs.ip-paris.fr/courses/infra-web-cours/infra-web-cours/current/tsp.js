
function newHTTPRequest() {
	var xhttp;

	if (window.XMLHttpRequest) {
		/* IE7+, Firefox, Chrome, Opera, Safari */
		xhttp=new XMLHttpRequest();
	} else {
		/* code for IE6, IE5 */
		xhttp=new ActiveXObject('Microsoft.XMLHTTP');
	}

	return xhttp;
}

function doURL(url) {
	return url + '?timestamp=' + new Date().getTime();
}

function transfer(newElmt, node, withAttributes=false) {
  while(node.firstChild) {
    var cur = node.firstChild;
    node.removeChild(cur);
    newElmt.appendChild(cur);
  }

  if(withAttributes && node.hasAttributes())
	  for(var i=0; i<node.attributes.length; i++) {
		  newElmt.setAttribute(node.attributes[i].name, node.attributes[i].value);
	  }

  return newElmt;
}

function rename(node, tagName, withAttributes=true) {
  var newElmt = document.createElement(tagName);

  transfer(newElmt, node, withAttributes);
  node.parentNode.replaceChild(newElmt, node);

  return newElmt;
}

function doCodes(node) {
    var containers = node.getElementsByClassName('code-container');

    for(var i=0; i<containers.length; i++) {
        var cur = containers[i];
        var prettify = cur.hasAttribute("data-code-prettify");
        var lang = cur.getAttribute("data-code-prettify");
        var url = cur.getAttribute("data-code-url");
        var gobble = cur.getAttribute("gobble-whitespace");
        if (typeof gobble == 'undefined')
            gobble = 0;

        if(url) {
            var xhttp = newHTTPRequest();

            xhttp.open('GET', doURL(url), true);
            xhttp.onload = function(xhttp, content, prettify, lang) {
                return function(e) {
                    if(xhttp.status == 200 || xhttp.status == 0) {
                        content.innerHTML = 
                            xhttp.responseText.replace(/\t/g, '  ').replace(/</g, '&lt;').replace(/>/g, '&gt;');

                        if(typeof PR !== 'undefined' && prettify)
                            content.innerHTML = PR.prettyPrintOne(content.innerHTML, lang);
                    } else {
                        content.innerHTML = "<h2 style='color:red; text-align:center'>Error " + xhttp.status + ": unable to load code</h2>";
                    }
                };
            }(xhttp, cur, prettify, lang);
            xhttp.send(); 
        } else {
            if(typeof PR !== 'undefined' && prettify) {
                let lines = cur.innerHTML.split('\n');
                console.debug(lines);
                lines = lines.map(line => line.replace(eval("/^ {" + gobble + "}/"), ""));

                cur.innerHTML = PR.prettyPrintOne(lines.join('\n'), lang);
            }
        }
    }
}

function doWeeks() {
	var weeks = document.getElementsByClassName('current-week');
  
  if(weeks.length > 0) {
		var cur = weeks[0].getAttribute('data-current-week');
		cur = cur == null ? 0 : cur;

		var mins = Array.prototype.slice.call(document.getElementsByClassName('min-week'), 0);

		for(var j=0; j<mins.length; j++) {
			var min = mins[j].getAttribute('data-min-week');
			min = min == null ? 0 : min;
      if(cur < min)
			  mins[j].parentNode.removeChild(mins[j]);
		}
  }
}

function dotoggle(node, active, inactive) {
	if(node.classList.contains(active)) {
		node.classList.add(inactive);
		node.classList.remove(active);
	} else {
		node.classList.add(active);
		node.classList.remove(inactive);
	}
}

function doSolutionContainers(node) {
  var containers = node.getElementsByClassName('solution-container');
  for(var i=0; i<containers.length; i++) {
      containers[i].classList.add('hasjs');
  }
}

function doToggles(node, wrap, displaySoluce, preprint) {
  var states = {
    'chapitre': { display: true,          open: true },
    'exercice': { display: true,          open: true },
    'question': { display: true,          open: true },
    'solution': { display: displaySoluce, open: wrap | preprint },
    'tip':      { display: true,          open: preprint },
    'details':  { display: true,          open: preprint }
  };

  var toggles = node.getElementsByClassName('toggle');
  for(var i=0; i<toggles.length; i++) {
    var toggle = toggles[i];
    var to = toggle.getAttribute('data-toggle-to');
    if(to) {
      var target = document.getElementById(to);
      if(target) {
        var state = states[to.split('-')[0]];
        state = typeof state === 'undefined' ? { display:true, open: true } : state;

        if(!state['display']) {
          toggle.classList.add('d-none'); /* wp */
          target.classList.add('inactive');
        } else {
          var is_open = state['display'] && state['open'] && (preprint || !toggle.hasAttribute('unwrap'));
          toggle.classList.add(is_open ? 'on' : 'off');
          target.classList.add(is_open ? 'active' : 'inactive');

			    toggle.onclick = function(toggle, target) {
				    return function(ev) {
					    dotoggle(toggle, 'on', 'off');
					    dotoggle(target, 'active', 'inactive');
					    ev.stopPropagation();
				    };
			    }(toggle, target);
        }
      }
    }
  }
}

function proceedPage(node, wrap, displaySoluce, preprint) {
  doToggles(node, wrap, displaySoluce, preprint);
  doSolutionContainers(node);
  doCodes(node);
}

function proceedAllInOne(wrap, displaySoluce, preprint) {
	var all = document.getElementsByClassName('all-in-one-container');

	for(var i=0; i<all.length; i++) {
		if(!all[i].getAttribute('done')) {
			all[i].setAttribute('done', 'true');
			var cl = all[i].getAttribute('data-all-class');
			cl = !cl ? "all-in-one" : cl;

			var nav = document.getElementById('chapters-list');

      if(nav) {
				var elmts = nav.getElementsByClassName(cl);

				for(var k=0; k<elmts.length; k++) {
					if(elmts[k].getAttribute('ignore') == null) {

						var xhttp = newHTTPRequest();
						var node = document.createElement('span');

						all[i].appendChild(node);

						xhttp.open('GET', elmts[k].href, true);
						xhttp.onload = function(xhttp, node) {
							return function(e) {
								var parser = new DOMParser();
								var doc = parser.parseFromString(xhttp.responseText, "text/html");
								var content = doc.getElementById('main-content');

								if(content)
									node.innerHTML = content.innerHTML;

								proceedPage(node, wrap, displaySoluce, preprint);
							}
						}(xhttp, node);

						try {
							xhttp.send();
						} catch(err) {
							if(document.location.protocol == 'file:') {
								node.innerHTML = "La politique de sécurité du navigateur est probablement trop sévère pour voir une page sans un serveur web. Essayez les solutions proposées <a href='https://github.com/mrdoob/three.js/wiki/How-to-run-things-locally'>ici</a>.";
							} else {
								node.innerHTML = "Erreur: " + e.message;
							}
						}
					}
				}
			}
		}
	}
}

function selectics(selectObject) {
	var boxes = document.getElementsByClassName('icsbox');
  var url = document.location.origin + 
            document.location.pathname + 
            "?ics=" + encodeURIComponent(selectObject.value) +
            "&unique=" + Date.now();

	for(var i=0; i<boxes.length; ++i) {
    boxes[i].style.display = 'inline-block';
    boxes[i].innerHTML = '<a href="' + url + '">' + url + '<a>';
  }
}

function bootstrap() {
	var qs = (function(a) {
		if (a == '') return {};
		var b = {};
		for (var i = 0; i < a.length; ++i) {
			var p=a[i].split('=', 2);
			if (p.length == 1)
				b[p[0]] = '';
			else
				b[p[0]] = decodeURIComponent(p[1].replace(/\+/g, ' '));
		}
		return b;
	})(window.location.search.substr(1).split('&'));

	var wrap = 'wrap' in qs && qs['wrap'] !== 'false';
  var ignoreWeek = 'ignoreWeek' in qs && qs['ignoreWeek'] !== false;
	var displaySoluce = (typeof forceSoluce !== 'undefined' && forceSoluce) || ('soluce' in qs && qs['soluce'] !== 'false');
	var preprint = 'preprint' in qs && qs['preprint'] !== 'false';
	var root = document.getElementsByTagName('body')[0];

	if(preprint)
		root.setAttribute('preprint', true);

  if(!ignoreWeek)
	  doWeeks();
	proceedPage(root, wrap, displaySoluce, preprint);

	proceedAllInOne(wrap, displaySoluce, preprint);
}

document.body.onload = bootstrap;
