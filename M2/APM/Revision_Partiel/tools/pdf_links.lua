-- PDF files live two levels below the assembled Markdown documents.
function Link(element)
  if not element.target:match("^%a[%w+.-]*:") and
     not element.target:match("^[#/]" ) then
    element.target = "../../" .. element.target
  end
  return element
end

function Image(element)
  if not element.attributes.width then
    element.attributes.width = "110mm"
  end
  return element
end

function Blocks(blocks)
  local result = pandoc.List()
  local i = 1
  while i <= #blocks do
    local block = blocks[i]
    if block.t == "Para" and #block.content == 1 and
       block.content[1].t == "Image" then
      result:insert(pandoc.RawBlock("latex",
        "\\begin{center}\\begin{minipage}{\\linewidth}\\centering"))
      result:insert(block)
      local caption = blocks[i + 1]
      if caption and caption.t == "Para" and
         caption.content[1] and caption.content[1].t == "Emph" then
        result:insert(caption)
        i = i + 1
      end
      result:insert(pandoc.RawBlock("latex", "\\end{minipage}\\end{center}"))
    else
      result:insert(block)
    end
    i = i + 1
  end
  return result
end
