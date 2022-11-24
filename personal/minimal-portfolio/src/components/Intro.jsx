import React from 'react';

function Intro(){
    return (
        <div className = "flex items-center justify-center flex-col text-center pt-20 pb-6">
            <h1 className = "text-4xl md:text-7x1 dark:text-white mb-1 md:mb-3 font-bold">Dausen</h1>
            <p className = "text-base md:text-xl mb-3 font-medium">Computer Science Student at The University of Alabama</p>
            <p className = "text-sm mx-20 mb-6 font-bold">Welcome to my website! My name is Dausen if you couldn't already tell, and I appreciate your time to check out my hard work. 
                I plan on graduating from the University of Alabama with a degree in computer science in the spring of 2024. After this, I'm honestly not quite sure what the plan is. I 
                currently work at Central Mesa in downtown Tuscaloosa as a bartender and shift lead, and while I love my coworkers, management, and the restaurant industry as a whole, 
                I can't see myself working in the industry forever. Anyways, enough about me not knowing what I wanna do when I grow up. Here's a link to my {'   '}
                <a href = "https://github.com/dausenm/dausen"
                target= "_blank"
                className="text-cyan-600 hover:underline underline-offset-2 decoration-2 decoration-red-600"
                rel="noreferrer noopener"
                >
                    github
                </a>
                {'   '} if you're interested in checking that out. Otherwise, check out the cool projects I have on display below and if I get the contact part of the website working,
                feel free to reach out!
                <br />
                Thanks Again!
            </p>
        </div>
    )
}

export default Intro;