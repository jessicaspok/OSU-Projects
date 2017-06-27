#ifndef GAME_ELEMENTS_CHAR_HPP
#define GAME_ELEMENTS_CHAR_HPP

vector<string> charLongDesc = {
							"You see Beth, a short petite brunette wearing some modern and simple attire.",
							"You see Claire, she has aubern hair that flows down her back, her attire much like something out of the 1950's.",
							"You see Sam, dressed to the nines in denim. He has dirty blonde hair",
							"You see Frank, wearing the white jacket a medical examiner would wear. He is a tall, large man with a kind face",
							"You see Trent, wearing an all black attire. His sleeves are rolled up on his button down shirt. He has blonde hair.",
							"You see Trevor, a teen, wearing some grunge style attire with long, blonde hair covering half of his face.",
							"You see Moose, a man with a rather rough, grizzled face. He is wearing a plaid shirt over a white tank-top.",
							"You see Abe, dressed in a nice, somewhat expensive looking suit with french cuffs. He has a tall, commanding appearance with piercing dark eyes.",
							"You see Rory, an older gentleman in a white jacket. He has a rather small stature, and his hazel eyes look wise as he looks back."	
						};

vector<vector<string>> charDialog = {
				/*0*/		{"*Sniffles* Hello, *Sniffles* who’s there?\n*Sniffles* huh? *Sniffles* \nOh, of course, please come in!\n",  
							 
				/*1*/		 "I was *sniffles* here all night that night, with Claire, watching movies.\n",
							 
				/*2*/	     "*Siffles* I don’t know...I don’t know why anybody would have wanted to hurt my Bobby!\n"
							 "*Sobs* You know what...yeah, maybe...I don’t know if he’d do it, but I do know...you should check Sam.\n"
							 "If he isn't home, he's probably hanging out with that degenerate, Moose.\n",
							 
				/*3*/		 "Too much of his medication!? No, that’s impossible. Bobby had an injury that's been taking a while to heal. It hurts a lot, but\n"
							 "his old man had problems with prescription drugs and he was worried he might get an addiction so I would get the\n"
							 "refills and dole out each dose when appropriate!\n"							 
							 "The bottle, it’s right here on the table...um, well...it was. It was right here!\n"
							 "(Beth looks around frantically for the bottle)\n"
							 "I don’t know where it’s at, I’m sorry...I’ll keep looking.\n"},  //beth
							 

				/*0*/		{"Hi, I’m Claire, Bobby was a friend of mine, mostly because he’s dating my best friend, Beth.\n"
							"I don’t really know a whole lot about him, but I’ll try and help if you have any questions.\n", 
							
				/*1*/		 "Hi, can I help you? Oh, yeah, that night... I was here with Beth.\n"							 
							 "We watched some movies and then I got tired and went home.\n",
							 
				/*2*/		 "His medication? No, I knew he was dealing with an injury but outside of that I know nothing. Sorry.\n"
							 "Have you talked to Moose?\n(She pulls you aside)\n *WHISPERS* You know, cuz he owed Moose a lot of money,"
							 " maybe he had something to do with\nit, or maybe Bobby took the pills and took too much cuz he owed so much?\n",
							 
				/*3*/		 "That crazy son of a bitch Trent! We argued becuase he is still in love with me amd threatened me if I didn't get back \nwith him."
							 "Look, I... didn't want to say anything before, but I...I was secretly in love with Bobby...and Trent knew it. \nHe must have thought"
							 "that I wouldn't be with him since I wanted to be with Bobby. He must have had something to do with \nBobby's death! I'm scared!"},  //claire
							 
							 
				/*0*/		{"Hey, I’m Sam. I was Bobby’s friend...best friend. I uh, can’t believe this happened to him. He was such a great guy, \nyou know? It’s just, too unbelieveable...I keep thinking I’ll just walk by his place and he’ll be there, working on his \ncar.\n",  
				/*1*/		"Yeah, what’s up? \nMe? Yeah, I was at the bar that night, switching back and forth between drinking with Moose and drinking with Bobby.\n",
				/*2*/		"Look, I get what you are trying to do, but I didn’t do it...you’re wasting your time. Just, get out of here, I won’t let \nsnoop you about my stuff.\n",
				/*3*/		"Are you kidding me, you went into my house!? Those emails mean nothing! I mean, they did, sure I’ve always had a thing \nfor Beth, but she loved Bobby. That doesn’t mean I’d kill my best friend for her! I’m not crazy! Look, aside from some \nemails, you have nothing on me. Go snoop somewhere else.\n"},  //sam
							
				/*0*/		{"I’m Frank, nice to meet you. Pretty exciting, huh? I mean, it’s sad he died...but I haven’t had anything more than old \npeople croaking in this small town till this happened. Oh, shoot...that doesn’t make me sound like I have motive, does \nit?\n",  
				/*1*/		"Ah, Detective, hope it’s going well.\nWell, so far nothing out of the usual. I’m waiting for a tox screen to finish processing. I’ve examined him externally \nbut all I’ve got is a minor case of Eczema on his arms.\n",
				/*2*/		"I definitely have something for you. The tox report came back, Bobby had highly elevated levels of a drug in his \nsystem. Here’s a copy of the report."},  //frank - medical examiner
							
				/*0*/		{"Hey, I’m Trent, you must be that detective from Big City they said they were bringing down.\nLook, Bobby was a great guy, well loved...I can't imagine this was anything more than an accident\n"
							"Anyways, best of luck with this, if you want a beer, just take one...it's on the house. Oh, you probably want some names...who was here, well, Moose and Sam were here.",  
				/*1*/		"Hello, Sir...something to drink?\n", 
				/*2*/		"Bobby, drinking? No, well yeah. He wasn’t drinking alcohol because of his medication. \nI was bringing him non-alcoholic drinks.\n", 
				/*3*/		"That sound...it must have come from the small hidden room in the back of the closet.\nLook, I swear I don't do anything I shouldn't with it! Here, I'll go open it up for you.",
				/*4*/		"Trevor? He's at my house, I am his legal guardian...ever since our parents died in a car accident."}, //Trent
							
				/*0*/		{"Huh, who are you? Oh, yeah, hey, I’m Trevor, Trent’s little brother. I (yawns) didn't really know Bobby, sorry.\n", 
				/*1*/		"Oh, hey Sir, uh, need somethin’?\n", 
							
				/*2*/		"Sorry, I was sleeping. Yeah, I was in the hidden room, I know Trevor leaves some homemade whiskey from a fella outside \ntown he sells out of the bar in there... so I went to get a little, please don’t tell on me! \nI had to go back and get my wallet since I accidentally dropped it in there last night\n"							
							"waiting. Before I could head out I had to wait for Trent and Claire to stop talking out back.\n"							
							"I couldn’t tell much, I just know Trent was yelling at Claire, he was real mad about something, I don’t know\n"},  //trevor
							
							
				/*0*/		{"Who is it!? If you can’t see the sign, I don’t care much for nosey people.\n"
							"Alright, fine, come in...but this better be quick.\n",
							
 				/*1*/		 "Yeah, waddya want!?\n"						 
							 "An Alibi!? I was at the bar ya numbskull!\n",
 							 "So what I sent him some threatening messages, just cuz we aint friends doesn’t mean I killed him.\n"
							 "Look, don’t you try’da pin this mess on me, I aint do nothin’, it’s that girlfriend of his...Beth,\n"
							 "she’s who you should be talk to. Now get outta here!!\n",
							 
							 "Yeah, I “loaned” him some money for whatevers but come payback time the guy couldn’t fork anything up. \nThe guy owes me some dough and I gotta reputation to uphold, or peoples gonna think they can walk allover ol’ Moose.\n"},  //moose
							 
							
				/*0*/		{"Hey, I’m the police Captain, but you can call me Abe. The boys here don’t normally deal with homicides given the rarity,\n"
							"so we sure are glad you could come out this way to help out. Anything you need, just let me know.\n"
							"By the way, that phone on my desk belonged to Bobby, go ahead and take it for your investigation.",
							
				/*1*/		"What can I do for you, Detective? If you get a chance, you should go talk to the medical examiner, Frank, at the Morgue.\n",
							
				/*2*/		"You have some suspicions about Sam huh? Well, I can’t imagine anyone in this town doing such a thing so I’ll be \nobjective about it.\nI figured you would need a warrant for the homes here, so I went ahead and got one, it's right there on the desk.",
							
				/*3*/		"I hope the investigation is going well, however, I have nothing new for you.",
							
				/*4*/		"If you have someone you want to arrest, let me know.\n"},  //abe: police captain
							
							
				/*0*/		{"Welcome to Rory’s Pharmacy, where the prices are low but the quality is high! What can I get for you, something for \nyour ailments or a few groceries, perhaps?\n",
							
				/*1*/		"Hello Sir, what can I get for you?\n", 
							
				/*2*/		"Uh huh, we do sell that here. Ok let me just check my system here and see if I can help.” Rory types in something into \nthe computer and waits. After a minute of scrolling about he snaps to. “Here we go, It seems that Bobby had a \nprescription for that medication. It looks like that last refill was just a few days ago. Huh, Bobby didn’t pick it up \nhimself though...it was Beth, Beth is in here for paying for and picking it up for him. She did that for him, so sweet.\nGo ahead and take the receipt if you need it."}   //rory - pharm
						};						
#endif