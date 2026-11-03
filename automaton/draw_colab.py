from html import escape
from IPython.display import SVG, display
import math

parts = ['<svg xmlns="http://www.w3.org/2000/svg" width="1800" height="730" viewBox="0 140 1800 730"><defs><marker id="arrow" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="8" markerHeight="8" orient="auto-start-reverse"><path d="M 0 0 L 10 5 L 0 10 z" fill="black"/></marker></defs><rect width="1800" height="900" fill="white"/>']
positions = {
    '0': (100, 630), '1': (290, 520), '2': (470, 520),
    '3': (670, 200), '4': (870, 200), '5': (1070, 200),
    '6': (1270, 200), '-1': (1470, 200),
    '7': (670, 520), '8': (870, 520), '9': (1070, 520),
    '10': (1270, 520), '-2': (1470, 520),
    '11': (290, 750), '-3': (470, 750),
    'error0': (670, 810), 'errorMid': (1640, 355)
}

def text(x, y, value):
    parts.append(f'<text x="{x}" y="{y}" font-family="Times New Roman,serif" font-size="24" text-anchor="middle" dominant-baseline="middle" paint-order="stroke" stroke="white" stroke-width="5" stroke-linejoin="round" fill="black">{escape(value)}</text>')

def path(value, arrow=False):
    marker = ' marker-end="url(#arrow)"' if arrow else ''
    parts.append(f'<path d="{value}" fill="none" stroke="black" stroke-width="1.8"{marker}/>')

def edge(a, b, label, label_position=None):
    x1, y1 = positions[a]
    x2, y2 = positions[b]
    dx, dy = x2 - x1, y2 - y1
    t1 = 1 / math.sqrt((dx / 38)**2 + (dy / 29)**2)
    radius2 = 34 if b.startswith('-') else 38
    height2 = 34 if b.startswith('-') else 29
    t2 = 1 / math.sqrt((dx / radius2)**2 + (dy / height2)**2)
    path(f'M {x1 + dx*t1} {y1 + dy*t1} L {x2 - dx*t2} {y2 - dy*t2}', True)
    lx, ly = label_position or ((x1 + x2)/2, (y1 + y2)/2 - 18)
    text(lx, ly, label)

path('M 20 630 L 60 630', True)
path('M 80 605 C 20 510, 180 510, 120 605', True)
text(160, 525, 'space, TAB, CR, LF')

edge('0', '1', 'i', (195, 555))
edge('0', '11', '1-9', (195, 705))
edge('1', '2', 's')
edge('2', '3', 'a', (560, 345))
edge('2', '7', 'd')
for a, b, label in [
    ('3', '4', 'l'), ('4', '5', 'p'), ('5', '6', 'h'),
    ('6', '-1', 'a'), ('7', '8', 'i'), ('8', '9', 'g'),
    ('9', '10', 'i'), ('10', '-2', 't'), ('11', '-3', '0-9')
]:
    edge(a, b, label)

path('M 870 549 C 870 625, 620 625, 490 545', True)
text(700, 608, 's')
path('M 1270 549 C 1270 725, 650 725, 490 545', True)
text(1000, 682, 's')

path('M 138 630 L 470 650')
path('M 290 549 L 470 650')
path('M 470 549 L 470 650')
path('M 290 721 L 470 650')
parts.append('<circle cx="470" cy="650" r="3" fill="black"/>')
path('M 470 650 C 535 660, 575 810, 636 810', True)
text(568, 743, 'other')

for x, bend in [(670, 355), (870, 325), (1070, 295), (1270, 265)]:
    path(f'M {x} 229 C {x} {bend}, 1380 355, 1470 355')
for x, bend in [(670, 355), (870, 385), (1070, 415), (1270, 445)]:
    path(f'M {x} 491 C {x} {bend}, 1380 355, 1470 355')
parts.append('<circle cx="1470" cy="355" r="3" fill="black"/>')
path('M 1470 355 L 1606 355', True)
text(1540, 333, 'other')

for state, (x, y) in positions.items():
    final = state.startswith('-') or state.startswith('error')
    label = '-4' if state.startswith('error') else state
    if final:
        parts.append(f'<circle cx="{x}" cy="{y}" r="34" fill="white" stroke="black" stroke-width="1.8"/><circle cx="{x}" cy="{y}" r="28" fill="none" stroke="black" stroke-width="1.5"/>')
    else:
        parts.append(f'<ellipse cx="{x}" cy="{y}" rx="38" ry="29" fill="white" stroke="black" stroke-width="1.8"/>')
    text(x, y, label)

parts.append('</svg>')
svg = ''.join(parts)
display(SVG(svg))
