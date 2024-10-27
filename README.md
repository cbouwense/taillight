# taillight

Generate a CSS stylesheet automatically from an HTML document.

## Example

### Input HTML

```html
<body class="m-0">
  <main class="w-100% mb-8rem p-2rem z-1 flex column gap-1rem fs-1.5rem">
  </main>
</body>
```

### Output 

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

### Quick start

```sh
make
./taillight
```

### Long version
```sh
# Compile via Makefile (uses clang)
make

# Or compile however you want
cc -o taillight taillight.c
zig cc 

# Default input is ./index.html and default output is ./taillight.css 
./taillight

# Or you can specify what you want
./taillight ../path/to/input.html ./path/to/output.css
```
