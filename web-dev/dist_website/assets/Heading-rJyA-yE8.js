import{r as s,t,y as f}from"./index-Dk0KL4Ml.js";const b=({text:r,className:o,action:a,icon:i})=>{const l=s.useRef(null),x=s.useCallback(e=>{const c=l.current;if(!c)return;const n=c.getBoundingClientRect(),u=e.clientX-(n.left+n.width/2),d=e.clientY-(n.top+n.height/2);c.style.transform=`translate(${u*.35}px, ${d*.35}px)`},[]),p=s.useCallback(()=>{const e=l.current;e&&(e.style.transform="translate(0, 0)")},[]);return t.jsxs("div",{children:[t.jsx("style",{children:`
          .Btn::before {
            background: #9900ff;
            content: "";
            position: absolute;
            top: 200%;
            left: -50%;
            z-index: 1;
            transition: all 0.4s ease-in-out;
            width: 100%;
            height: 400%;
            filter: blur(15px);
            transform: translate(-50%, -50%) rotate(60deg);
            }
            
            
          .Btn:hover::before {
            height: 10%;
            top: -10%;
            left: 110%;
          }

          .Btn span {
            position: relative;
            z-index: 5;
            color: white;
          }
        `}),t.jsxs("button",{ref:l,onMouseMove:x,onMouseLeave:p,className:`Btn py-2 px-5 text-base flex justify-center items-center gap-2.5 relative font-normal cursor-pointer overflow-hidden transition-transform duration-300 ease-out text-transparent rounded-xl sm:min-w-45 text-nowrap nunito-sans bg-linear-to-r from-[#8c00ff] from-60% to-[#3e0077] ${o}`,onClick:a,children:[t.jsx("span",{children:i}),t.jsx("span",{children:r})]})]})},m=s.memo(({hPlain:r,hColor:o,className:a="",tagline:i})=>t.jsxs(f.div,{initial:{opacity:0,y:20},whileInView:{opacity:1,y:0},viewport:{once:!0},transition:{duration:.6},className:`text-center text-white pb-4 sm:pb-8 ${a}`,children:[t.jsxs("h3",{className:"text-3xl sm:text-5xl text-center league-spartan font-bold",children:[r," ",t.jsx("span",{className:"text-[#bb00ff]",children:o})]}),t.jsx("p",{className:"text-[16px] text-center pt-2 text-[#948597] px-10 sm:px-0",children:i})]}));m.displayName="Heading";export{b as B,m as H};
