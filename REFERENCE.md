# Taillight reference

A typical taillight class name consists of the following
```
{media}:{rule}-{value}{units}{important}
```
Here is a random set of example class names and how they get parsed

| Class name   | Media     | Rules                       | Value | Units     | Important |
|:-------------|:----------|:----------------------------|:------|:----------|:----------|
| `m-10rem`    | undefined | margin                      | 10    | rem       | no        |
| `uw:w-50%!`  | ultrawide | width                       | 50    | %         | yes       |
| `flex`       | undefined | display                     | flex  | undefined | no        |
| `c:py-12px!` | computer  | padding-top, padding-bottom | 12    | px        | yes       |

## Media queries

Prefix class names with a token representing the media and `:` to do media queries. 

| Token | Medium             | Query                      |
|:------|:-------------------|:---------------------------|
| m     | mobile             | @media (max-width: 768px)  |
| t     | tablet             | @media (min-width: 768px)  |
| c     | laptop / desktop   | @media (min-width: 1024px) |
| uw    | ultrawide screen   | @media (min-width: 3840px) |

## Supported styles

### Width

| Class  | Property   |
|:------ |:-----------|
| w      | width      |
| minW   | min-width  |
| maxW   | max-width  |

### Height

| Class  | Property    |
|:------ |:------------|
| h      | height      |
| minH   | min-height  |
| maxH   | max-height  |

### Padding

| Class  | Property       |
|:------ |:---------------|
| p      | padding        |
| pt     | padding-top    |
| pb     | padding-bottom |
| pl     | padding-left   |
| pr     | padding-right  |
| px     | padding-left   |
|        | padding-right  |
| py     | padding-top    |
|        | padding-bottom |

### Border

| Class  | Property      |
|:------ |:--------------|
| b      | border        |
| bt     | border-top    |
| bb     | border-bottom |
| bl     | border-left   |
| br     | border-right  |
| bx     | border-left   |
|        | border-right  |
| py     | border-top    |
|        | border-bottom |
| brad   | border-radius |

### Margin

| Class  | Property      |
|:------ |:--------------|
| m      | margin        |
| mt     | margin-top    |
| mb     | margin-bottom |
| ml     | margin-left   |
| mr     | margin-right  |
| mx     | margin-left   |
|        | margin-right  |
| my     | margin-top    |
|        | margin-bottom |

### Position

| Class    | Property           |
|:---------|:-------------------|
| relative | position: relative |
| absolute | position: absolute |
| fixed    | position: fixed    |


alignStart
  align-items: flex-start
alignEnd
  align-items: flex-end
alignCenter
  align-items: center
alignBaseline
  align-items: baseline
alignStretch
  align-items: stretch
breakAll
  word-break: break-a
breakWord
  word-wrap: break-word
basis
  flex-basis

c
  color
column
  flex-direction: column
dot
  "list-style-type: disc"
  "margin-left: 1.5rem"

flex
  "display: flex"
fs
  "font-size"
gap
  "gap"
grid
  "display: grid"
gridCol
  
grow
flex-grow

justifyStart
justify-content: flex-start
justifyEnd
justify-content: flex-end
justifyCenter
justify-content: center
justifyBetween
justify-content: space-between
justifyAround
justify-content: space-around
justifyEvenly
justify-content: space-evenly
justifyStretch
justify-content: stretch
left
left
lightShadow
  "box-shadow: 0 0 16px 0 rgba(255, 255, 255, 0.2)
lightShadowSmall
  box-shadow: 0 0 8px 0 rgba(255, 255, 255, 0.2)

right
          right
rounded
          border-radius: 8px;
row
          flex-direction: row
shadowSm
          box-shadow: 0 1px 2px 0 rgb(0, 0, 0, 0.05)
shadow
          box-shadow: 0 1px 3px 0 rgb(0, 0, 0, 0.1), 0 1px 2px -1px rgb(0, 0, 0, 0.1)
shadowMd
          box-shadow: 0 4px 6px -1px rgb(0, 0, 0, 0.1), 0 2px 4px -2px rgb(0, 0, 0, 0.1)
shadowLg
          box-shadow: 0 10px 15px -3px rgb(0, 0, 0, 0.1), 0 4px 6px -4px rgb(0, 0, 0, 0.1)
shadowXl
          box-shadow: 0 20px 25px -5px rgb(0, 0, 0, 0.1), 0 8px 10px -6px rgb(0, 0, 0, 0.1)
shadowXxl
          box-shadow: 0 25px 50px -12px rgb(0, 0, 0, 0.25)
shadowInner
          box-shadow: inset 0 2px 4px 0 rgb(0, 0, 0, 0.05)
shadowNone
          box-shadow: 0 0 #0000
shrink
          flex-shrink
sticky
          position: sticky
          top: 0
          box-sizing: border-box
top
          top
        underlineDots
          text-decoration: underline dotted

        wrap
          word-wrap: break-word
        z