# kroman

Kroman is a Korean hangul romanization tool.

It's currently implemented as a command line utility, a ruby gem,
a python package, and a nodejs package. Editor plugins will be implemented.

This is the C command line utility.

It's lightweight, efficient, and enjoyable.

## Implementations

- [kroman command line tool](https://github.com/cheunghy/kroman)
- [kroman ruby gem](https://github.com/cheunghy/kroman-gem)
- [kroman python package](https://github.com/cheunghy/kroman-py)
- [kroman nodejs package](https://github.com/cheunghy/kroman-js)

## Installation
### with brew on OS X
On OS X, you can install kroman with brew
```
brew tap cheunghy/kroman
brew install kroman
```

### manually
You may download the source code and make it. No dependencies are needed.
```
make install
```

## Basic usage
```
kroman < nice_korean_song.txt > nice_singable.txt
```

```
Before:

희망은 잠들지 않는 꿈

After:

heui-mang-eun jam-deur-ji anh-neun ggum

```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/cheunghy/kroman.

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
