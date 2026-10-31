# Zenith: My Journey of Making a Minimalist Computer Which Can Run Programs and Bringing it to Life in Hardware
## Introduction
Hey, I'm **Auritro** (aka `semismash`, you can also just call me 'smash' if you like), currently an 18 year-old 2nd year student pursuing ECE, and this is perhaps the first time that I'm writing a proper blog post. Think of this post as an ~~bored student's~~ **aspiring engineer's** first dive into *"proper writing"*, I guess... :D
In any case, starting off things strong, I've recently built a *little project* called **"Zenith Core"**, essentially a **tiny** and **minimalist** computer made from scratch, although more accurately described as a *microcontroller*... but **computer** sounds better. 
Anyways, having designed each part of this project myself, I'd like to share how I have **designed each component of the stack**, keeping things generally *informal*. However, in this blog, I'll also get into much of the *nitty gritty* **technical details**, **design decisions** I made, **implementation flow**, and a *teensy bit* about the journey to get here.
Lastly, *I'd like to begin the people who have supported me throughout my journey, not just for this project, but overall till now, for the last couple of rough years I have had. It's not a lot of people, but I'm extremely grateful for the support I have gotten that has kept me going.*
> [Disclaimer]
> The project and every component of it have been designed and planned completely by a human(i.e. me). The vast majority of the core implementation has been done by me too. However, certain sections of the implementation (particularly the CLI tool, Makefile, and simulation bridges), debugging, and formatting of user-documentation have been done with the help of AI, although almost all AI changes were thoroughly human reviewed/tested. Lastly, this blog is entirely human written.

Now, **let's become serious**. Here's a **table of contents** for each section of this blog. Basically, a **quick reference** you can use instead of having to juggle between pages each time you want to find something.
> [Button]
> Check out the repository here: [Zenith Core Repository](https://github.com/semismash/Zenith-Core)
## Table of Contents
- Blog Introduction & Table of Contents
- Zenith Introduction and Explanation
- A Brief Introduction of RISC-V
- Hardware of Zenith Core: Design, Implementation, and Simulation
- Upgrading the Core for FPGA synthesis and Hardware Practicality
- BIOS Protocol: Design and Process
- BIOS Firmware: Design, Implementation, and Explanation of RV32I Assembly
- Client: Design and Implementation
- Integrating Components into a Single System & Simulation
- C Program Compilation and Support
- FPGA Synthesis and Hardware Testing
- Conclusion
## Zenith — Explained Piece-by-Piece
> [Journey]
> *A couple of months ago, during my summer, I had to go to Kolkata to visit my grandfather who was suffering from Stage 4 Cancer. During that time, I had been working on a custom Rust-based bare-metal OS kernel, as a fun little project to keep my mind off things... part of a larger project I'm working on, to make my own computer ecosystem from scratch, from CPU to OS to ISA to Language. Under pressure, I was able to craft something working, a basic kernel with scrollable display output, keyboard input, interrupts and segmentation, and a even level of multi-threading protection.*
> *That would end up being the last time I would ever see him. A pretty sad thought, but in an effort to keep going, I shifted my gears to working on a the CPU side of things. Up until then I had never actually made my own proper CPU apart from one in the Nand2Tetris course, so decided to use my SystemVerilog knowledge to give it a short. From there, `riscVia` was birthed, stood for "RISC-V is awesome!", and soon became the basis of what became **Zenith**.*

So, what is **Zenith**? Well, the *literal* meaning means to be the 'peak' or, more metaphorically, the **'culmination of something'**. And in a way, this is project kind of meant to mirror that, a culmination of my own projects and work over the last year.
But what exactly is this project about? Essentially, **Zenith Core** is a *minimalist* **computer** built from scratch, meant to see how a *seemingly mundane* **CPU core** can be used to **host a basic system** which can **load and run programs** and actually get it **working on hardware**, essentially turning it into a **general purpose machine** you can hold in the palm of my hand. While it's not a *traditional computer*, it can do everything a basic computer can:
- **Input**: Load programs and files
- **Process**: Run firmware and execute loaded programs
- **Output**: Present the output of said programs
- **Storage**: Store data locally on the device itself
Seems familiar? That's because it's just your *classic* **IPOS cycle**.
> [Objection]
> But... how does this make your *'Zenith'* or whatever different from just a regular old CPU core? Can't regular CPU cores just do the same thing?
> [Response]
> Good question. While it is true that a normal RISC-V (or whatever) CPU core can process information and store it using dedicated instructions, a basic simulation core you may be thinking of **cannot actively do anything unless you tell it to, nor can it actually use proper input or output.** It's essentially a dumb piece of silicon or RTL which only does what you tell it to do... i.e. instructions. **Zenith fills these very holes**, giving the CPU a voice, brain, and ear, essentially allowing the user to actually talk to the CPU and use it as a general purpose machine. More on this soon.

To construct **Zenith**, it helps us to split **Zenith's** components by **separation of responsibilities**. The design is *completely* **orthogonal**, meaning that every part of Zenith can decoupled from one another, yet *seamlessly integrates* to make a **functioning system**. I'd say this is pretty much a *necessity* when designing a system with so many interconnected components from scratch.
The main components of **Zenith** are listed here:
- **CPU Core**: The Hardware Heart of the Zenith
- **BIOS Firmware**: The Brain which resides in the Core and interfaces with the user
- **Client**: The User Client which can be used to connect with and interface with the BIOS
- **BIOS Protocol**: A common shared communication protocol between the BIOS and Client
- **Simulation**: The simulation used to test each component
- **FPGA**: The actual board on which the CPU was run
Remember these 6 basic components as essentially a **'single source of truth'** for this project as you read this blog. Basically, each component interacts with each other, serving a specific purpose, and getting our whole system to work with absolute cadence. :)
> [Advice]
> Something I've learnt a lot from developing projects that are as extensive as this is that **modularity and decoupling** is your friend that will carry you for a *LOOONG* time. Apart from simply front-loading complexity, designing every component to be separate from one another and communicate with each other using a shared medium saves a LOT of time in the long run, especially if you have multiple different parts which have different uses. And adding to this point - **DO NOT make one component do too many things at the same time**. Having learnt that the hard way, doing so drastically increases complexity and decreases debuggability. That being said, a *little bit* of *'monolith-icity'* and hardcoding is fine and even beneficial in the short-run if it reduces complexity for testing purposes and current scope.

Anyways, let's begin discussing the design and implementation flow one by one. Every topic mentioned below is in order of how I have implemented it, so think of it as if I'm kinda taking you on a trip down memory lane, and showing how each section of the project was crafted one by one.
## Wait, but... What IS a RISC-V ?!?
> [Tip]
> You may skip this section if you are already well-aware of RISC-V and the architecture.

Okay... a lot of you may be a bit new to all these, perhaps interesting computer architecture or low level programming, and just getting into this stuff. Good chance many of you have already heard of *RISC-V*, or *RV32I*, or similar terms like that, but there is a chance that you are still a bit fuzzy on what exactly it means, even if you know what it's associated with.
To put it simply - **RISC-V** is an **instruction set architecture (ISA)**. Think of an **ISA** as kind of its own protocol which the CPU uses to encode 'instructions' and hence understand what operations it has to execute. **RISC-V** is basically just that - it's own language which one can use to build a CPU core around. To be adherent to the **RISC-V specification**, i.e. to be considered a *'true'* **RISC-V core**, the CPU **must execute every valid combination and encoding of RISC-V instruction exactly to the extent the spec defines it**. To check the *full RV32I spec*, [click here](https://docs.riscv.org/reference/isa/v20260120/unpriv/rv32.html).
> [Doubt]
> Wait, then what is *RV32I* specifically, and why do I keep seeing it everywhere?
> [Answer]
> **RV32I** is essentially the specific version of the RISC-V that was used to build the CPU. RISC-V is basically a *'family'* of different ISAs that are, to an extent, cross compatible with each other, as long as they share the same word widths. While not *TRULY* inter-compatible, each variation of RISC-V has features that are similar or basically the same as other RISC-V variants, close enough that you could say it's all *one big happy family*... :)
> **RV32I** specifically stands for **"RISC-V 32-bit Base Integer"**. It's a base ISA, and perhaps one of the most common ones  you might have noticed in students' projects online... and for good reason! More about it explained below.

The **RV32I instruction set** has a few parameters that are worth keeping in mind when we design this CPU. A couple of these are **fundamental truths** that dictate the functioning of basically *ANY* program written on it, and I've summarized it pretty concisely here:
- **32-bit word size**: The CPU deals with and operates on values that are 32 bits wide.
- **32 GPRs**: GPR means general purpose register. These registers are where the data being operated upon by the CPU is stored. The RV32I spec required 32 of them, ordered `x0` to `x31`.
- **Hardwired zero register**: The `x0` register is always hardwired to all zeros. While seemingly pretty random, it plays a crucial rule, that we'll discover throughout the journey of designing.
- **40 base instructions**: Spans a variety of types and used for a variety of operations. Out of these, three specific instructions will not be implemented as specified, for reasons explained later.
- **32-bit fixed instruction width**: Every instruction is fixed at a 32-bits width. The program counter always increments a constant amount (4 with byte-wise addressing) during CPU execution, when not stalled.
Now, you may be wondering why seemingly EVERYONE is so crazy about RISC-V... I mean seems to be that everyone and their grandma is implementing their own RISC-V core nowadays as their next biggest 'third year or final year student project' or something like that, and that I'm possibly a hypocrite for calling it out ¯\\\_\(ツ)\_\/¯. But it's not without reason. RISC-V as pretty set up for success for academic fields, making it absolutely gold for students and researchers to use, and is the reason even I selected it for this project. Why...?
- **Elegant Consistency in Encoding**: Perhaps the biggest reason, and something that makes RISC-V especially elegant for me. Almost every field - the *opcode*, *source* and *destination registers*, *funct* fields etc. are all *ALWAYS* in the same position and width in whatever instruction they are in. The only exception is immediates, which are kind of 'chopped up and scattered' across the encoding space, and can be easily reconstructed later.
- **Overall Simplicity of Implementation**: RISC-V, and especially RV32I, was designed so that there are almost *no extra fancy little components* or 'gotchas' that show up later during implementation. For the most part, you can pretty much define a RISC-V compatible CPU with just the basic Fetch, Decode, Execution and Memory Access units, along with a PC and Register file. Of course, upgrading it requires more components, but is still very simple and straightforward.
- **A *VERY* Gracious Register Pool**: I mean, just look at it. *32 ENTIRE general purpose registers* in just the base spec. Not even AMD64 gives you that much! But seriously, this amount of space allows for beginners to write programs with a LOT of leeway, something that me (who is still not THAT old to this field) leveraged a good amount, as seen in the BIOS firmware section. The zero register is also a stroke of genius, as it allows many operations which would have otherwise taken multiple instructions to complete (like copy or jump and no-link) can be done in *just a single instruction*. Pretty neat!
- **Orthogonal Design**: RISC-V is pretty much one of the best examples on how to make an ISA that's *orthogonal*, where each feature *seamlessly integrates with one another*. Perhaps my favorite examples is more I-type instructions using 12-bit immediates, and the two specific U-type instructions use 20-bit immediates. And guess what? 12 + 20 = 32... meaning you can pretty much load a 32-bit value in just two instructions, with zero extra trouble. RISC-V overall has a LOT of examples of this orthogonality that I love, be it consistency in word and instruction sizing, or simplicity of instructions, and is also a good reason as to why writing firmware for it was still pretty doable.
> [Image]
> Picture of the 6 basic encoding structures of RV32I instruction
![[Pasted image 20261027212518.png]]

Anyways, that's enough RISC-V appreciation for now, can't believe I spent 15 minutes writing it. It's time to move on to the **actual implementation**.
## The Core — Designed and Tested
Okieee, time to begin designing the actual hardware! :D
> [Journey]
>  *I'd just finished `riscVia`, my single-cycle RV32I core. Felt like a pretty nice achievement at the time, but also kinda breezed through it in a couple of days, given my prior knowledge in computer architecture, and the elegance of the RV32I ISA. Now, the next stage was pipelining... cuz' how else would my CPU run at high frequencies if the entire core updated at once? Well... a bit of a confession, but I was not sure about that part either, I didn't really have experience with timing analysis or even thought about it much, just kind of went on by going through Patterson and Hennessey, seeing their pipelining explanation, and figuring out along the way what each thing meant.*
>  *Eventually, I figured out my own design for pipeline registers, a teensy bit unconventional but otherwise textbook. Initially resolved all with stalling, before figuring out all the data hazards (refer to that one table in page C-40) and implementing forwarding along with the dedicated stall unit. Soon, begun working on designing a branch predictor from scratch, no references. Ended up on a 2-bit dynamic BP with 1024-entry PLRU set associative BTB.*
>  *Over time, it seemed like I slowly understood the elegance of the craft... specifically figuring stuff out. While at first, I doubted how pipelining would ever be useful, slowly shifting from 'implementing' to 'proactively learning', seeing how each component worked and interacted with each other, leading me to the phase of designing components from my own intuition.*
>  *In the end, the core in Zenith would be vastly different from the `riscVia` core. Stripped out branch-prediction, added UART & MMIO, and other changes. But in each iteration of the predecessor, I learnt something new, and more elegant than the last, which has stuck by me unto this day of writing my blog on the very design decisions I made with Zenith.*

Now... let's start from the basics. In the previous section, we just discussed about RISC-V, and even laid out a couple of specs related to it. And now, it's time to actually turn it into something realizable.
First, we need to choose our hardware description language (HDL) to define our circuits. I chose SystemVerilog, being the main hardware language I know, and also being one of the most used industry-standard ones to design such high-performance circuits today. But truthfully, any valid hardware language works.
Next, decide the model and architecture of the CPU. Since we have already laid out the architecture for RISC-V in the previous section, the specification gives us a good framework to work with, and build the CPU from there. In addition, there are a couple of neat little additions to upgrade our CPU, so as to improve performance and efficiency by a LOT... mentioned right after the next paragraph :)
Lastly, the CPU needs to actually work on our hardware. Of course, while we can just simulate a regular CPU core and synthesize it on our board, we won't really have a proper way to communicate with it, which will be covered in the next section.
Anyways, in this project, this CPU has three distinct versions, that I created through different iterations. I'll go through each one with a level of depth, but not TOO in depth (there will be another blog post coming for that, so stay tuned :P). There are a total of 4 main versions of the CPU, where I'll mainly be covering three of them, as the fourth version was not used in the project.
- Single Cycle: The simplest version of the core. Outlines all different parts, such as the controller, datapath, memory, and other related components. Everything executes in a single clock cycle.
- Pipelined: Different parts of the CPU disaggregated into different distinct stages. Instructions progress to the next stage every clock cycle, kind of like a conveyor belt, but introduces certain hazards that are to be resolved via stalls and flushes.
- Forwarded: Upgrade to pipelining for resolving most data hazards, switching stalling for directly forwarding the executed values to the newer instructions, increasing instruction throughput.
- Branch Prediction: \[NOT COVERED\] Upgrade to pipelining to mitigate control hazards, by predicting the outcome of the branch based on its address to prevent unnecessary flushes in the pipeline.
While designing my core, I created each version in the aforementioned chronological order. As a result, I'll cover each part one by one, covering it from the perspective of an engineer designing it for the first time.
### Single Cycle: The Humble Beginnings
Let's begin with the very heart of the core! After all, we need something to actually compute our instruction, haha :P
But before we start, let's ask ourselves a simple question: What EXACTLY does a CPU do?
Sure, I mean it computes something based on the instruction... but how do you think it does it?
Well, as you probably know, instructions are encoded in binary format. As we had previously established, RISC-V instructions are 32-bits, stored in little-endian order and contiguously in memory. Specifically, the instruction memory. Then, we need to decode the instruction into proper signals that tell the CPU what to do. We also need to do the actual computation - execution. In addition, we need to write back the results back to our CPU registers, and perhaps access the data memory if required... ooh would you look at that, we got a model.
What I just described is the model with which almost all general purpose CPUs are designed - the famous "Fetch → Decode → Execute" cycle.
In many cases, the Execute stage is split into three more stages, 'Execute', 'Memory Access', and 'Write Back', which overall adds up to 5 main stages of our CPU's execution.
Apart, from this, there is a different way to model the CPU: By the CPU's dataflow. Based on the separation of concerns between what directs the CPU (instructions), and what the CPU actually deals with (data), we get a strict boundary between two components - the Controller and the Datapath.
With this, we have constructed two models on our CPU which we can refer from:
1) On the basis of separating instruction and data flow -
	-  Controller: The part of the CPU that controls the flow of data by utilizing the instruction (includes Program Counter, Decoder, Fetch Unit etc.).
	- Datapath: The part of the CPU that handles the data itself, as dictated by the controller (includes Register File, ALU, LSU etc.).
2) On the basis of instruction processing stages -
	- Instruction Fetch (IF): Fetch the instruction from the instruction memory. Contains the Fetch Unit and the Program Counter which gives the address to the instruction.
	- Instruction Decode (ID): Decodes the fetched instruction into individual control signals that are to be used by the CPU in the following stages, and retrieve the required data from the register file.
	- Execute (EX): Calculate the output of the instruction from the fetched data and give the output accordingly.
	- Memory Access (MEM): Access the data memory if required, either by loading the data into the CPU, or by storing data from the CPU back in the data memory.
	- Write Back (WB): Write back the final calculated or loaded into the register file for reuse, using the specified register address.
## Our Core works in Software... But what about in the Real World?
## The BIOS Protocol — A Language so We can Talk to Our Core
## BIOS Firmware — 1500 Deterministic Lines of Pure Assembly, and Pure Agony
## We have the Core. Now we need the Client.
## Tying It All Together
## C Program Compilation and Loading — Making a "True" Computer You Can Run Anything On*
## The Final Stretch — FPGA Implementation, and Seeing Our Creation Come to Life
## Conclusion