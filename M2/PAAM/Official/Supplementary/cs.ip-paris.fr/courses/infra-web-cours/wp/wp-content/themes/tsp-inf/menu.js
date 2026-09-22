
function isEmptyNode(node) {
  return !(node && ((node.nodeType == Node.TEXT_NODE && !/^\s*$/.test(node.textContent)) || 
                    node.nodeType == Node.ELEMENT_NODE));
}

function nextSibling(node) {
  if(node)
    for(var cur=node.nextSibling; cur; cur=cur.nextSibling) {
      if(!isEmptyNode(cur))
        return cur;
    }

  return null;
}

function doParagraphs(root) {
	var ps = root.getElementsByTagName('p');
  
  for(var p of ps) {
    var first = p.parentNode.firstChild;
    first = isEmptyNode(first) ? nextSibling(first) : first;
    if(first == p)
      p.classList.add('first-p');

    var next = nextSibling(p);
    if(next && next.nodeType == Node.ELEMENT_NODE && (next.tagName === 'UL' || next.tagName == 'OL'))
      p.classList.add('with-list');
  }
}

function isVisited(visited, node) {
	return visited.includes(node);
}

function markVisited(visited, node) {
	if(!isVisited(visited, node))
		visited.push(node);
}


function dropdownClick(ev, button, desc) {
	ev.stopPropagation();

	var root = desc['buttons'][button.id]['root'];
	var visited = [];

	if(button.classList.contains('active')) {
		var rect = button.getBoundingClientRect();
		if(ev.clientX < rect.left || ev.clientX > rect.right || ev.clientY < rect.top || ev.clientY > rect.bottom)
			return;

		button.classList.remove('active');
		var parent = desc['buttons'][button.id]['parent'];
		button = parent ? desc['buttons'][parent.getAttribute('data-from')]['button'] : null;
	} else {
		button.classList.add('active');
	}
	
	if(button && button.classList.contains('active')) {
		var buttonDesc = desc['buttons'][button.id];

		markVisited(visited, button);

		/* show targets */
		var targets = buttonDesc['targets'];
		for(var i=0; i<targets.length; i++) {
			targets[i].classList.add('highlight');

			if(!targets[i].classList.contains('show')) {
				targets[i].classList.add('show');
				if(targets[i].classList.contains('fade-height'))
					targets[i].style.height = targets[i].scrollHeight + "px";
			}

			markVisited(visited, targets[i]);

			for(var parent=targets[i].parentNode; parent!=root; parent=parent.parentNode) {
				if(parent.classList.contains('dropdown-target')) {
					var bd = desc['buttons'][parent.getAttribute('data-from')];
					markVisited(visited, bd['button']);

					var bdt = bd['targets'];
					for(var j=0; j<bdt.length; j++) {
						markVisited(visited, bdt[j]);
						bdt[j].classList.remove('highlight');
					}
				}
			}
		}
	}

	/* cleanup */
	var allTargets = desc['roots'][root.id]['targets'];
	for(var i=0; i<allTargets.length; i++) {
		var target = allTargets[i];

		if(!isVisited(visited, target) && target.classList.contains('show')) {
			target.classList.remove('show');
			if(target.classList.contains('fade-height')) {
				target.style.height = target.scrollHeight + "px";
				(function(e) {
					var id = requestAnimationFrame(function() {
						e.style.height = 0;
						cancelAnimationFrame(id);
					});
				})(target);
			}
		}
	}

	var allButtons = desc['roots'][root.id]['buttons'];
	for(var i=0; i<allButtons.length; i++) {
		if(!isVisited(visited, allButtons[i]))
			allButtons[i].classList.remove('active');
	}
}

function doDropdowns() {
	var desc = { };
	var buttons = document.getElementsByClassName('dropdown-button');
	var rootId = 0;

	desc['buttons'] = { };
	desc['roots'] = { };

	for(var button of buttons) {
		var parent = null;
		var root;
		for(root=button.parentNode; root!=document && !root.classList.contains('dropdown-area'); root=root.parentNode)
			if(!parent && root.classList.contains('dropdown-target'))
				parent = root;
		root = root == document ? button : root;

		if(!root.id)
			root.id = "dropdown-area-" + rootId++;

		if(!desc['roots'][root.id])
			desc['roots'][root.id] = { 'buttons': [], 'targets': [] };

		desc['roots'][root.id]['buttons'].push(button);
		desc['buttons'][button.id] = {};
		desc['buttons'][button.id]['root'] = root;
		desc['buttons'][button.id]['button'] = button;
		desc['buttons'][button.id]['targets'] = [];
		desc['buttons'][button.id]['parent'] = parent;

		button.onclick = function(button, desc) {
			return function(ev) { dropdownClick(ev, button, desc); }
		}(button, desc);
	}

	var targets = document.getElementsByClassName('dropdown-target');

	for(var target of targets) {
		if(target.getAttribute('data-from')) {
			var button = desc['buttons'][target.getAttribute('data-from')];
			button['targets'].push(target);
			desc['roots'][button['root'].id]['targets'].push(target);

			if(target.classList.contains('fade-height'))
				target.addEventListener("transitionend", (function(e) {
					return function() {
						if(e.classList.contains('show'))
							e.style.height = 'auto';
						else
							e.style.removeProperty('height');
					}
				})(target));
		}
	}

	//var stopClicks = document.getElementsByClassName('stop-click');
	//for(var i=0; i<stopClicks.length; i++)
	//stopClicks[i].onclick = function(ev) { console.log('stop click'); ev.stopPropagation(); };
}

function doMenus() {
	var menus = document.getElementsByClassName('tsp-menu');
	var n = 0;

	for(var i=0; i<menus.length; i++) {
		var menu = menus[i];
		var uls = menu.getElementsByTagName('UL');

		for(var ul of uls) {
			var li;
			for(li=ul.parentNode; li!=document && li.tagName!='LI'; li=li.parentNode);

      var parent = ul.parentNode;
      var container = document.createElement('div');

      parent.replaceChild(container, ul);
      container.append(ul);

			container.classList.add('dropdown-target');
			container.classList.add('fade-height');

			if(li == document) {
				container.setAttribute('data-from', menu.getAttribute('data-toggler'));
			} else {
				if(!li.id)
					li.id = "dropdown-button-" + n++;
				li.classList.add('dropdown-button');
				container.setAttribute('data-from', li.id);
			}
		}

		var lis = menu.getElementsByTagName('LI');

		for(var li of lis) {
			/* remove leading space after menu-icon */
			//if(li.firstChild && li.firstChild.nodeType == Node.TEXT_NODE && /\S/.test(li.firstChild.textContent)) {
			var wrapper = document.createElement('span');
      var first = li.firstChild;
      wrapper.classList.add("menu-entry");
			li.replaceChild(wrapper, first);
			wrapper.append(first);
		  //}

			var toggleIcon = document.createElement('div');
			toggleIcon.classList.add('menu-caret-icon');
			var toggle = document.createElement('div');
			toggle.classList.add('menu-caret');
			toggle.append(toggleIcon);
			li.prepend(toggle);
			if(li.classList.contains('dropdown-button'))
				toggle.classList.add('has-children');
		}
	}

	doDropdowns();

  /* do the p here */
  doParagraphs(document);
}

document.addEventListener('DOMContentLoaded', doMenus);
