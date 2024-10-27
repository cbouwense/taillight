# taillight

Generate a CSS stylesheet automatically from an HTML document.

## Quick start

```sh
make
./taillight
```

## Example

### Input HTML

index.html
```html
<body class="m-0">
  <main class="w-100% mb-8rem p-2rem z-1 flex column gap-1rem fs-1.5rem">
  </main>
</body>
```

### Output CSS

taillight.css
```css
.m-0 { margin: 0; }
.w-100\% { width: 100%; }
.mb-8rem { margin-bottom: 8rem; }
.p-2rem { padding: 2rem; }
.z-1 { z-index: 1; }
.flex { display: flex; }
.column { flex-direction: column };
.gap-1rem { gap: 1rem; }
.fs-1\.5rem { font-size: 1.5rem; }
```

## Compile and Run

```sh
# Compile via Makefile (uses clang)
make

# Or compile however you want
cc -o taillight taillight.c
zig build-exe taillight.c

# Default input is ./index.html and default output is ./taillight.css 
./taillight

# Or you can specify what you want
./taillight ../relative/path/to/input.html ./relative/../path/to/output.css
```
