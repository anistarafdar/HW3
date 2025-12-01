# HW3
Homework 3: Design, Extensibility, and Maintenance Report

This report breaks down the big changes I made in part 3A and how those design choices played out (for better or worse) when I had to extend them in 3B.

The main goal of 3A was to take the original, rigid program and break it into modular pieces using interfaces. Here is the list of structural changes I made:

Problem class: I stripped the Problem class down to a bare-bones interface called IProblem that only cares about questions and answers. This meant the specific implementation (like the arithmetic problem class) became just one type of problem, rather than the only type.

Parser interface: moved the file-reading logic out of main and into a Problem Bank Parser Interface. This allowed me to create a specific latex parser for the original format without locking the system into it. (I had anticipated something for 3B to be like a JSON bank to parse problems then build it into a latex file, hence this desgin decision)

Selector interface: pulled the random selection logic out and put it into an IProblemSelector interface. The original "stupid" shuffling logic went into it’s own class.

Writers: I separated the output logic into an interface. This let me create simple and fancy test writer as two different tools that were more decoupled.

 I moved the validation logic (like counting topics or difficulty points) into a constraint base class with subclasses like TopicConstraint and DifficultyConstraint (this decison decision was not something I expected to be an issue for the continuation on 3b)

Moving from 3A to 3B was a mixed bag. Some parts of the design worked perfectly, while other parts exposed some "tech debt" where I hadn't fully decoupled things, since my 3A was incomplete. I would like to think that if I had planned ahead better this headache wouldn’t have been, but when can you ever predict the future of an evolving codebase?

What worked:

Task 1 worked very well after I understood how it was hiding the answer key with the headers. Having a test writer interface made it trivial to make a new writer with minimal structural changes, I just had to write a new writer that formatted the output differently. I didn't have to touch the existing writers at all. The design did exactly what it was supposed to do here. SOLID principles helped and forward thinking worked well here.

Part of task 2 felt fine, swapping out the selection logic was also straightforward. I just wrote a new class that implemented the greedy algorithm. The generator didn't care which selector it was using, so plugging it in was simple to do after figuring out the code for the algorithm in C++.

What did not:

Constraints classes. This was the biggest headache. In 3A, I left the constraint logic tightly coupled inside the constraint header file instead of separating it into implementation files. When 3B introduced a new problem type for MathProblem I had to write ugly logic that basically was if new data type then do this if old data type do that inside that header to keep the old generators from crashing. It… works, but in real code this would be inviting your codebase to be in refactor hell. I would want to fix this asap if I had time for it.

I spent way too much time trying to make the regex work for the problem bank. It turned out to be too annoying to use, either the compiler would scream about escape characters or I’d just have weird behavior of it not properly working. I eventually had to scrap it and write a simple sequential string search to get it working reliably, which isn’t simple at all in C++, but it compiled.

Because I didn't set up a Makefile that works initially, I ran into massive errors when trying to compile the different versions. I still don’t think my makefile works properly, I’ve just been one shotting the exe with a large line.

What to change:

In hindsight, the major mistake I made in 3A was being too lax with the way I designed constraints. I should have treated them like full citizens with their own rights with their own .h and .cpp files instead of cramming them into one header. If I had done that, I wouldn't have needed the messy dual-casting logic in 3B and other headaches in terms of organization that made it hard to track my changes. I could have just written new constraints for the new data type without touching the old ones. I remember thinking in 3A that the way constraints worked it probably would be safe to do it like that. I was naive.

Also, I should have realized earlier that the regex is more of a headache and eye sore than just a bunch of C++ string loops. It isn’t pretty, but neither is regex. And regex didn’t let me compile. SO yeah.

To build, try the Make. It might be broken, will fix in a few.

make all

