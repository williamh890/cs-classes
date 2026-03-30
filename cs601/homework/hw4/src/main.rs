use regex::Regex;

fn is_valid_url(possible_url: &str) -> bool {
    let url_re = Regex::new(r"(?x)
        ^(http(s?):\/\/)?
        (www.)?
        [a-z]+[-a-z0-9]*
        \.(com|edu|org|rs)
        (\/([a-zA-Z]+[-a-zA-Z0-9]+)*)*
        (\/|[a-zA-Z]+.[a-zA-Z]+)?
        (\#[a-z]+)?
    $").unwrap();

    url_re.is_match(possible_url)
}

fn main() {
    let good_urls = [
        "google.com",
        "http://google.com",
        "http://bad-site.com",
        "https://www.formula1.com/",
        "https://github.com/ASFHyP3",
        "https://www.alaska.edu/uaonline",
        "https://www.alaska.edu/uaonline/",
        "https://alaska.edu/uaonline/profile",
        "https://www.alaska.edu/uaonline/profile1/",
        "https://rust-lang.org/learn/get-started/",
        "https://docs.rs/regex/latest/regex/#syntax",
        "https://github.com/github/gitignore/blob/main/Rust.gitignore",
        "webserver.com/index.html",
        "webserver.com/index.html#fragmenthere",
    ];

    for url in &good_urls {
        let is_url = is_valid_url(url);
        assert!(is_url, "Failed to match URL {}", url);
        println!("{}: {}", is_url, url);
    }

    let bad_urls = [
        "THIS NO GOOD",
        "BLKJSDGIOO{U#@)(USDFL:FKj)}",
        "htttp://google.com",
        "google..com",
        "helloworld.com\\"
    ];

    for url in &bad_urls {
        let is_url = is_valid_url(url);
        assert!(!is_url, "False match on URL {}", url);
        println!("{}: {}", is_url, url);
    }
}
