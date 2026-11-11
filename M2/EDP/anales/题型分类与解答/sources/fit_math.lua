function Math(el)
 if el.mathtype == 'DisplayMath' then
  return pandoc.RawInline('latex', '\\begin{center}\\begin{adjustbox}{max width=\\linewidth}\\(\\displaystyle '..el.text..'\\)\\end{adjustbox}\\end{center}')
 end
 return el
end
function Table(el)
 local n=0
 for _,body in ipairs(el.bodies) do n=n+#body.body end
 if n<=12 then
  return {pandoc.RawBlock('latex','\\Needspace{'..tostring((n+3)*1.5)..'\\baselineskip}'),el}
 end
 return el
end

function Image(el)
 if el.src:match('network2025') or el.src:match('td3_identical') or el.src:match('td3_heterogeneous') then el.attributes.width='160mm' end
 if el.src:match('td3_duplicated') then el.attributes.width='120mm' end
 return el
end
