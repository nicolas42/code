originally from https://github.com/benawad/gowiki

modified it so that it saves and serves arbitrary html,css,javascript, which is supposed to be insecure but it's cool.

Is it more insecure?

I don't know what html+javascript could do from a server.  I think in order to use it in an attack you'd need a different mechanism
that would actually run the file.

I actually don't understand why it would be insecure.  The code is all executed client-side.  And in the other version whewre they 
were only saving text files there's no reason why they couldn't also save some code and then run it through some other mechanism.

I guess it could be used to make a malicious website, if such a thing exists these days.  A phishing website could be made possibly.

But then again this kind of website can be made anywhere really.  Hmmm....  There doesn't seem to be any particular security risks.  

Perhaps I just don't know that much about security.

Just remember to put salt on all your sha3 hashed passwords.
