function Link(el)
  if not el.target:match('^%a[%w+.-]*:') and not el.target:match('^[#/]') then
    el.target = '../../' .. el.target
  end
  return el
end
function Image(el)
  el.attributes.width = '145mm'
  return el
end
function Para(el)
  if #el.content == 1 and el.content[1].t == 'Image' then
    return {pandoc.RawBlock('latex', '\\begin{center}'),el,
            pandoc.RawBlock('latex', '\\end{center}')}
  end
end

function CodeBlock(el)
  return {pandoc.RawBlock('latex', '\\begin{minipage}{\\linewidth}'),
          el,
          pandoc.RawBlock('latex', '\\end{minipage}\\par')}
end

-- Keep each short exam statement, including its code, together on one page.
function Pandoc(doc)
  local blocks = pandoc.List()
  local in_statement = false
  for _, block in ipairs(doc.blocks) do
    if block.t == 'Header' then
      local title = pandoc.utils.stringify(block.content)
      if title == 'Énoncé / 题目' then
        blocks:insert(pandoc.RawBlock('latex', '\\begin{minipage}{\\linewidth}'))
        in_statement = true
      elseif in_statement then
        blocks:insert(pandoc.RawBlock('latex', '\\end{minipage}\\par'))
        in_statement = false
      end
    end
    blocks:insert(block)
  end
  doc.blocks = blocks
  return doc
end
