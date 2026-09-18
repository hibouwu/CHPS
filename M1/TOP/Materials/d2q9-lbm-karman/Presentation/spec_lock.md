## canvas
- viewBox: 0 0 1280 720
- format: PPT 16:9

## colors
- bg: #FFFFFF
- secondary_bg: #F4F7FA
- tertiary_bg: #EAF0F6
- primary: #1565C0
- accent: #E65100
- secondary_accent: #0277BD
- text: #1A2332
- text_secondary: #546E7A
- text_tertiary: #90A4AE
- border: #CFD8DC
- success: #2E7D32
- warning: #C62828
- success_bg: #E8F5E9
- info_bg: #E3F2FD
- accent_bg: #FFF3E0
- error_bg: #FFF5F5
- success_light: #F1F8E9
- accent_light: #FFF8F0

## typography
- font_family: "Microsoft YaHei", Arial, sans-serif
- font_family_xml: &quot;Microsoft YaHei&quot;, Arial, sans-serif
- code_family: Consolas, "Courier New", monospace
- code_family_xml: Consolas, &quot;Courier New&quot;, monospace
- body: 20
- title: 40
- subtitle: 26
- annotation: 14
- cover_title: 52
- hero_number: 72
- display_hero: 120
- kpi_label: 13

## icons
- library: chunk-filled
- inventory: bolt, chart-bar, shield, cpu, memory, layers, rocket, check-circle, x-circle, arrow-right, code, speedometer

## images
- cover_flow: images/cover_flow.jpeg

## page_rhythm
- P01: anchor
- P02: dense
- P03: dense
- P04: breathing
- P05: dense
- P06: dense
- P07: dense
- P08: dense
- P09: dense
- P10: dense
- P11: dense
- P12: anchor

## forbidden
- Mixing icon libraries
- rgba()
- `<style>`, class, `<foreignObject>`, textPath, @font-face, `<animate*>`, `<script>`, `<iframe>`, `<symbol>`+`<use>`
- `<g opacity>` (set opacity on each child element individually)
- HTML named entities (`&nbsp;`, `&mdash;`, etc.) — use raw Unicode
