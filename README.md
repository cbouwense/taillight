# taillight

Generate a CSS stylesheet automatically from an HTML document with Tailwind-like class names.

## Quick start

```sh
make
./taillight
```

## Example

### Input HTML

```html
<main class="w-100% uw_w-75% bg-#181818">
  <div class="flex gap-1rem">
    <span>one</span>
    <span>two</span>
    <span>three</span>
  </div>
</main>
```

### Output CSS

```css
.w-100\% {
  width: 100%;
}
.bg-\#181818 {
  background-color: #181818;
}
.flex {
  display: flex;
}
.gap-1rem {
  gap: 1rem;
}
/* Ultrawide */
@media (min-width: 3886px) {
  .uw_w-75\% {
    width: 75%;
  }
}
```
(ommitted some default styles for clarity)

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
./taillight ./path/to/input.html ./path/to/output.css

# There's a watch mode too, so you don't remember to rerun taillight after modifying the html
./taillight --watch
./taillight -w input.html output.css
```

## Documentation

Probably coming
