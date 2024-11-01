# taillight

Generate a CSS stylesheet automatically from an HTML document with Tailwind-like class names. No external dependencies (except glibc).

## Quick start

```sh
make
./taillight
```

## Example

### Input HTML

```html
<main class="w-100% uw:w-75% bg-#181818">
  <div class="flex column gap-1rem"></div>
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
.column {
  flex-direction: column;
}
.gap-1rem {
  gap: 1rem;
}
/* Ultrawide */
@media (min-width: 3886px) {
  .uw\:w-75\% {
    width: 75%;
  }
}
```
(ommitted some default styles for clarity)

## Usage

### Compile

```sh
# Compile via Makefile (uses clang)
make

# Or compile however you want
gcc -o taillight taillight.c
zig build-exe taillight.c
```

### Run

```sh
# Default input is ./index.html and default output is ./taillight.css 
./taillight

# Or you can specify what you want
./taillight ./path/to/input.html ./path/to/output.css

# I highly recommend the watch mode (-w|--watch) so you don't have to remember to rerun taillight every time you modify your html
./taillight --watch
./taillight -w input.html output.css
```

### Run the tests
```sh
make test

# Optionally silence the Make output
make test -s
```

## Documentation

Probably coming ¯\\\_(ツ)_/¯
