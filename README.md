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
<body class="m-0 c_mx-10%">
  <main class="uw_relative uw_absolute w-100%! mb-8rem p-2rem z-1 flex column gap-1rem fs-1.5rem">
    <a class="hoverable">link with cool effect</a>
  </main>
</body>
```

### Output CSS

taillight.css
```css
/* Some boilerplate styles */
.m-0 {
  margin: 0;
}
.w-100\%\! {
  width: 100% !important;
}
.mb-8rem {
  margin-bottom: 8rem;
}
.p-2rem {
  padding: 2rem;
}
.z-1 {
  z-index: 1;
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
.fs-1\.5rem {
  font-size: 1.5rem;
}
.hoverable {
  color: var(--text-primary-color);
  transition: color 0.25s ease;
}
.hoverable:hover {
    color: var(--text-secondary-color);
}

/* Computer (desktop / laptop) */
@media (min-width: 1024px) and (max-width: 3840px) {
  .mobile { display: none; }
  .tablet { display: none; }
  .computer { display: inherit; }
  .ultrawide { display: none; }
  :root { font-size: 18px; }
  .c_mx-10\% {
    margin-left: 10%;
    margin-right: 10%;
  }
}

/* Ultrawide */
@media (min-width: 3840px) {
  .mobile { display: none; }
  .tablet { display: none; }
  .computer { display: none; }
  .ultrawide { display: inherit; }
  :root { font-size: 18px; }
  .uw_relative {
    position: relative;
  }
  .uw_absolute {
    position: absolute;
  }
}

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

## Documentation

Coming soon!
