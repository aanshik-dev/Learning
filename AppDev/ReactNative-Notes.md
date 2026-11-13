<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **REACT NATIVE NOTES** [ **/>**](https://reactnative.dev/docs/getting-started) 🔥🐦‍🔥

<br>

## 🐦‍🔥 WHAT IS REACT NATIVE?

React Native ek open-source UI software framework hai jise Meta (formerly Facebook) ne create kiya hai. Iska core philosophy hai: **"Learn once, write anywhere"**. Iska matlab ye nahi ki "Write once, run everywhere" bina kisi platform consideration ke; balki aap React ke mental model aur JavaScript/TypeScript ke knowledge se Android, iOS, iPadOS, macOS, Windows aur Android TV tak ke native apps design kar sakte hain.

⚡ **Hinglish Analogy (Web vs Hybrid vs React Native):**

- **Cordova / Ionic (WebView Hybrid):** Ye bilkul ek mobile browser wrapper ke jaisa hai. Jaise ek website ko WebView ke andar frame karke chalana. Isme native feeling nahi aati aur heavy animations par app laggy ho jaata hai.
- **Flutter:** Flutter apna khud ka canvas leke baithta hai aur C++ engine (Impeller/Skia) se har pixel khud draw karta hai. Isme system UI controls nahi hote, balki native jaise look-alike widgets draw hote hain.
- **React Native:** React Native real Native components create karta hai. JavaScript sirf mastermind (brain) ki tarah instruction bhejti hai, lekin screen par paint hone wala view sach me Android ka `android.widget.TextView` aur iOS ka `UILabel` hota hai. Yani 100% true native performance aur accessibility.

<br>

### 🔥 React JS vs React Native

| Feature                      | React JS (Web)                                     | React Native (Mobile)                                                 |
| :--------------------------- | :------------------------------------------------- | :-------------------------------------------------------------------- |
| **Target Platform**          | Web Browsers (Chrome, Safari, Firefox)             | Mobile OS (Android, iOS, Native Platforms)                            |
| **Rendering Engine**         | Browser DOM (Document Object Model)                | Native Platform UI Framework (UIKit on iOS, Android Views on Android) |
| **Layout Engine**            | Standard CSS / Browser Box Model                   | Yoga Engine (C++ based Flexbox implementation)                        |
| **Basic UI Building Blocks** | `<div>`, `<p>`, `<span>`, `<img>`, `<button>`      | `<View>`, `<Text>`, `<Image>`, `<Pressable>`                          |
| **Styling Paradigm**         | CSS stylesheets, CSS Modules, Tailwind Web         | JavaScript Object (`StyleSheet.create`), Flexbox by default           |
| **JavaScript Engine**        | V8 (Chrome), JavaScriptCore (Safari), SpiderMonkey | Hermes (Default & Optimized for Mobile), JavaScriptCore (JSC)         |
| **Routing / Navigation**     | React Router DOM, Next.js File-system Routing      | React Navigation, Expo Router (Native Stack & Navigation Tree)        |
| **Platform APIs**            | Web APIs (`window`, `document`, `localStorage`)    | Native Modules (`AsyncStorage`, Camera, Geolocation, Sensors)         |

<br>

### 🔥 Architecture Breakdown: Legacy vs New Architecture

React Native ki architecture time ke sath revolutionize hui hai. Deep understanding ke liye dono models ko samajhna mandatory hai.

```text
======================= LEGACY ARCHITECTURE =======================
+-------------------+        JSON ASYNC BRIDGE        +---------------------+
| JavaScript Thread | <=============================> |    Native Thread    |
| (React Code, JS)  |  Serialization / Deserialization| (Android / iOS UI)  |
+-------------------+                                 +---------------------+
                                  |
                                  v
                        +--------------------+
                        |   Shadow Thread    |
                        |   (Yoga Layout)    |
                        +--------------------+

========================= NEW ARCHITECTURE =========================
+-------------------+                                 +---------------------+
| JavaScript Thread | <---------- JSI (C++) --------> |    Native Thread    |
|  (Hermes Engine)  |    Direct Memory Pointer Calls  | (Android / iOS UI)  |
+-------------------+                                 +---------------------+
          |                                                      |
          +-----------------> [ Fabric UI ] <--------------------+
          +--------------> [ TurboModules (C++) ] <---------------+
```

⚡ **Legacy Architecture (The Bridge Bottleneck):**

1. **JavaScript Thread:** Yahan aapka React code, business logic, state updates aur API calls execute hote hain.
2. **Native Thread (Main / UI Thread):** Ye Android ka main thread ya iOS ka UIKit thread hai jo user gestures handle karta hai aur 60/120 FPS par pixels draw karta hai.
3. **Shadow Thread:** C++ Yoga layout engine yahan flexbox math compute karke absolute dimensions (`x, y, width, height`) nikalta hai.
4. **The Bridge:** JS Thread aur Native Thread directly ek doosre se baat nahi kar sakte the. Bridge ek asynchronous message queue thi.
   - JS thread data ko JSON stringify karta tha.
   - Bridge se serialised message pass hota tha.
   - Native side JSON parse karke execute karta tha.

⚡ **Hinglish Analogy (Single-lane Toll Bridge Jam):**
Socho do alag sheher hain: ek "JS Nagar" (Hindi bolne wala) aur doosra "Native Pur" (English bolne wala). Dono ke beech ek hi narrow bridge hai. Har instruction ke liye pehle chithhi likho (JSON Stringify), postman bridge cross karega (Bridge serialization overhead), fir wahan chithhi translate hoke padhi jayegi (JSON Parse). Agar user fast scroll karta hai ya swipe animation karta hai, to bridge par hazaron messages ka traffic jam lag jata hai, jiske wajah se "white blank screen flashes" aate the.

⚡ **The New Architecture (Fabric & TurboModules with JSI):**
New architecture ne Bridge ko completely eliminate kar diya hai.

1. **JSI (JavaScript Interface):** JSI ek lightweight, general-purpose C++ abstraction layer hai. Iske through JavaScript engine direct C++ host objects ke reference (memory pointers) hold kar sakta hai aur methods synchronously call kar sakta hai.
   - _Analogy:_ Ab postman ki zarurat nahi hai; JS aur Native ab ek hi room me baithe hain aur direct direct hand-to-hand pointer transfer kar rahe hain.
2. **Fabric (New Rendering System):** Yoga engine C++ me deeply integrated hai. UI calculations aur native tree updates direct C++ layer par synchronously execute ho sakte hain. Isse high-speed scrolling aur gesture tracking buttery-smooth ho jati hai bina kisi blank screen flicker ke.
3. **TurboModules:** Native hardware APIs (Bluetooth, Camera, Biometrics) pehle app startup par hi sare load hote the chahe zarurat ho ya na ho. TurboModules lazy loading support karte hain—jab tak feature call nahi hota, native module memory me load nahi hota.
4. **Hermes Engine:** Meta ka lightweight open-source JavaScript engine jo mobile devices ke liye specifically engineer kiya gaya hai.
   - Ahead-of-Time (AOT) bytecode compilation.
   - Extremely fast Time To Interactive (TTI).
   - Minimal memory footprint and small APK size.

<br>
<br>

## 🐦‍🔥 GETTING STARTED

React Native me app development start karne ke do primary workflows hote hain: **Expo** aur **React Native CLI (Bare React Native)**.

### 🔥 Expo vs React Native CLI

| Parameter               | Expo (Managed Workflow)                                    | React Native CLI (Bare Workflow)                               |
| :---------------------- | :--------------------------------------------------------- | :------------------------------------------------------------- |
| **Setup Complexity**    | Very Low. Zero native build tools required initially.      | High. Android Studio, JDK, Xcode, CocoaPods mandatory.         |
| **Android/iOS Folders** | Hidden by default (Prebuild generates on demand).          | Explicitly present (`android/`, `ios/`) from day one.          |
| **Native Custom Code**  | Custom config plugins / EAS Build / Prebuild.              | Direct Java/Kotlin & Objective-C/Swift file editing.           |
| **Testing on Device**   | Expo Go app scan QR code (Instant).                        | USB Debugging, Emulator, or Simulator build.                   |
| **Over The Air (OTA)**  | Built-in via EAS Update.                                   | Requires third-party tools like Microsoft CodePush.            |
| **Build System**        | Cloud builds via EAS (Expo Application Services) or local. | Local machine hardware (High RAM & CPU required).              |
| **Ideal Use Case**      | 90% modern production apps, rapid MVP, startups.           | Deep OS level integrations, custom hardware SDKs, legacy apps. |

⚡ **Kaunsa Choose Karein?**

- **Modern Expo Choose Karein:** Aaj ka modern Expo ab purana rigid Expo nahi raha. Expo Prebuild aur Config Plugins ki madad se aap koi bhi custom native library (C++, Kotlin, Swift) bind kar sakte hain. Production teams recommend karti hain Expo with EAS.
- **Bare CLI Choose Karein:** Agar aapke project me existing native Android/iOS codebase hai jisme React Native embed karna hai (Brownfield Integration) ya proprietary native SDKs hain jo direct build configurations inject karti hain.

<br>

### 🔥 Environment Prerequisites

⚡ **Core Requirements:**

- **Node.js:** Node LTS version (`>= 18.x` or `>= 20.x`).
- **Package Manager:** `npm`, `yarn`, ya `pnpm`.
- **Git:** Version control.
- **Watchman (Recommended on macOS/Linux):** Facebook ka file-watching service jo hot reloading fast karta hai.

⚡ **For Android Development (CLI & Local Builds):**

1. **Java Development Kit (JDK):** OpenJDK 17 mandatory.
2. **Android Studio:**
   - Android SDK Platform 34 (or latest recommended).
   - Android SDK Platform-Tools.
   - Android Virtual Device (AVD) / Emulator.
3. **Environment Variables Configuration (Windows PowerShell):**
   ```powershell
   [System.Environment]::SetEnvironmentVariable("JAVA_HOME", "C:\Program Files\Eclipse Adoptium\jdk-17.x.x-hotspot", "User")
   [System.Environment]::SetEnvironmentVariable("ANDROID_HOME", "$env:LOCALAPPDATA\Android\Sdk", "User")
   ```
   _System Path me add karein:_
   - `%ANDROID_HOME%\platform-tools`
   - `%ANDROID_HOME%\emulator`

<br>

### 🔥 Project Initialization Commands

⚡ **Expo Project Setup (Recommended):**

```bash
# Initialize modern Expo app with TypeScript
npx create-expo-app@latest MyExpoApp --template blank-typescript

# Navigate to project
cd MyExpoApp

# Start the Metro bundler server
npx expo start
```

⚡ **React Native CLI Setup (Community Bare Template):**

```bash
# Initialize pure React Native CLI project
npx @react-native-community/cli@latest init MyCliApp

# Navigate to project
cd MyCliApp

# Start Metro server in one terminal
npx react-native start

# Run Android build in another terminal
npx react-native run-android

# Run iOS build (macOS only)
npx react-native run-ios
```

<br>

### 🔥 Project Structure Breakdown

```text
MyCliApp/
├── android/               # Native Android project (Gradle, Java/Kotlin, AndroidManifest)
├── ios/                   # Native iOS project (Xcode project, Podfile, Swift/Obj-C)
├── node_modules/          # Installed dependencies
├── src/                   # Application source code (Components, Screens, Hooks)
│   ├── components/
│   ├── screens/
│   ├── navigation/
│   └── App.tsx            # Main root application component
├── app.json               # App configuration (Display name, slug, bundle identifiers)
├── babel.config.js        # Babel transpiler configuration (presets and plugins)
├── metro.config.js        # Metro bundler config (asset plugins, SVG transformers)
├── package.json           # Dependencies and project scripts
└── tsconfig.json          # TypeScript compiler configuration
```

⚡ **Key Config Files Explained:**

- `app.json`: App metadata store karta hai jaise package name, icon, splash screen config. Expo me ye master configuration file hoti hai.
- `metro.config.js`: Metro React Native ka dedicated JS bundler hai (jaise web ke liye Webpack ya Vite). Ye fast hot reload, bundle splitting, aur asset resolution handle karta hai.
- `babel.config.js`: JSX aur modern ECMAScript features ko Hermes-compatible JS me convert karta hai. Reanimated plugin hamesha isme last position par register hota hai.

<br>
<br>

## 🐦‍🔥 PRIMITIVE COMPONENTS (vs HTML / REACT DOM)

Web development me hum HTML tags use karte hain, lekin mobile operating systems me browser DOM exist nahi karta. Isliye React Native platform-agnostic core primitives provide karta hai jo platform ke native controls par map hote hain.

```text
Web DOM Element              React Native Primitive              Native Android / iOS Output
<div>               ===>     <View>                    ===>      ViewGroup / UIView
<p>, <span>         ===>     <Text>                    ===>      TextView / UILabel
<img>               ===>     <Image>                   ===>      ImageView / UIImageView
<input type="text"> ===>     <TextInput>               ===>      EditText / UITextField
<button>            ===>     <Pressable>               ===>      View with Touch Listener
```

<br>

### 🔥 `<View>` (The Universal Container)

`<View>` native container UI element hai. Ye Android ke `android.view.ViewGroup` aur iOS ke `UIView` me translate hota hai.

- Ye default Flexbox container hota hai.
- By default `flexDirection: 'column'` hoti hai.
- Ye non-scrollable hota hai.

```tsx
import React from "react";
import { View, StyleSheet } from "react-native";

export const ContainerBox = () => {
  return (
    <View style={styles.cardContainer}>
      <View style={styles.innerBadge} />
    </View>
  );
};

const styles = StyleSheet.create({
  cardContainer: {
    backgroundColor: "#1E1B4B",
    padding: 16,
    borderRadius: 12,
    borderWidth: 1,
    borderColor: "#4338CA",
  },
  innerBadge: {
    width: 24,
    height: 24,
    borderRadius: 12,
    backgroundColor: "#10B981",
  },
});
```

<br>

### 🔥 `<Text>` (The Typography Engine)

⚡ **Critical Rule:** React Native me plain raw string ko direct `<View>` ke andar nahi daal sakte. Har ek character compulsory `<Text>` tag ke andar wrap hona chahiye, warna red-screen error throw hoga: `Invariant Violation: Text strings must be rendered within a <Text> component`.

```tsx
import React from "react";
import { Text, StyleSheet } from "react-native";

export const TypographyExample = () => {
  return (
    <Text style={styles.baseText}>
      Welcome to <Text style={styles.highlightText}>React Native Mastery</Text>!
      Strings can be nested to inherit parent typography rules.
    </Text>
  );
};

const styles = StyleSheet.create({
  baseText: {
    color: "#E2E8F0",
    fontSize: 16,
    lineHeight: 24,
    fontFamily: "System",
  },
  highlightText: {
    color: "#38BDF8",
    fontWeight: "bold",
  },
});
```

<br>

### 🔥 `<Image>` (Asset vs Remote Handling)

Local static images aur network remote images ko load karne ke syntactic patterns me difference hota hai:

1. **Local Asset:** `require('./path/to/asset.png')` use karta hai. Isme width/height specify karna optional hai kyunki packager image dimensions compile time par read kar leta hai.
2. **Network Image:** `{ uri: 'https://...' }` use karta hai. Isme `width` aur `height` compulsory deni padti hai, warna image render nahi hogi (0x0 space consume karegi).

```tsx
import React from "react";
import { View, Image, StyleSheet } from "react-native";

export const ImageGallery = () => {
  return (
    <View style={styles.container}>
      {/* Local Asset Bundle */}
      <Image
        source={require("./assets/local_avatar.png")}
        style={styles.avatar}
        resizeMode="cover"
      />

      {/* Remote URI Asset */}
      <Image
        source={{
          uri: "https://images.unsplash.com/photo-1534528741775-53994a69daeb?w=500",
        }}
        style={styles.remoteBanner}
        resizeMode="cover"
      />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    gap: 16,
  },
  avatar: {
    width: 64,
    height: 64,
    borderRadius: 32,
  },
  remoteBanner: {
    width: "100%",
    height: 200,
    borderRadius: 16,
  },
});
```

<br>

### 🔥 `<TextInput>` (User Input Handling)

Web me input `e.target.value` se access hota hai. React Native me direct raw string `onChangeText` callback me milti hai.

```tsx
import React, { useState } from "react";
import { TextInput, StyleSheet, View, Text } from "react-native";

export const FormInput = () => {
  const [email, setEmail] = useState("");

  return (
    <View style={styles.fieldWrapper}>
      <Text style={styles.label}>Email Address</Text>
      <TextInput
        style={styles.input}
        placeholder="dev@example.com"
        placeholderTextColor="#64748B"
        value={email}
        onChangeText={(text) => setEmail(text)}
        keyboardType="email-address"
        autoCapitalize="none"
        autoCorrect={false}
      />
    </View>
  );
};

const styles = StyleSheet.create({
  fieldWrapper: {
    marginVertical: 8,
  },
  label: {
    color: "#94A3B8",
    marginBottom: 6,
    fontSize: 14,
  },
  input: {
    backgroundColor: "#0F172A",
    borderWidth: 1,
    borderColor: "#334155",
    borderRadius: 8,
    paddingHorizontal: 12,
    paddingVertical: 10,
    color: "#F8FAFC",
    fontSize: 16,
  },
});
```

<br>

### 🔥 Interactive Touchables & `<Pressable>`

Legacy components: `<TouchableOpacity>` (press karne par opacity dip hoti hai), `<TouchableHighlight>` (underlay color dikhata hai).
Modern React Native me **`<Pressable>`** industry standard hai kyunki ye deep interaction lifecycle states expose karta hai (`pressed`, `hovered`, `focused`).

```tsx
import React from "react";
import { Pressable, Text, StyleSheet } from "react-native";

interface PrimaryButtonProps {
  label: string;
  onPress: () => void;
}

export const PrimaryButton = ({ label, onPress }: PrimaryButtonProps) => {
  return (
    <Pressable
      onPress={onPress}
      style={({ pressed }) => [
        styles.buttonBase,
        pressed && styles.buttonPressed,
      ]}
      android_ripple={{ color: "#4338CA" }} // Native Android Ripple Effect
    >
      {({ pressed }) => (
        <Text style={[styles.buttonText, pressed && styles.textPressed]}>
          {label}
        </Text>
      )}
    </Pressable>
  );
};

const styles = StyleSheet.create({
  buttonBase: {
    backgroundColor: "#6366F1",
    paddingVertical: 14,
    paddingHorizontal: 24,
    borderRadius: 10,
    alignItems: "center",
    justifyContent: "center",
  },
  buttonPressed: {
    backgroundColor: "#4F46E5",
    transform: [{ scale: 0.98 }],
  },
  buttonText: {
    color: "#FFFFFF",
    fontSize: 16,
    fontWeight: "600",
  },
  textPressed: {
    opacity: 0.9,
  },
});
```

<br>

### 🔥 Platform Specific Primitives: SafeAreaView, StatusBar, KeyboardAvoidingView

1. **`SafeAreaView` / `react-native-safe-area-context`:** iPhone ke notch, dynamic island, aur Android navigation gesture bar ke peeche content ko chupne se bachata hai.
2. **`StatusBar`:** Phone ke top hardware status bar (battery indicator, clock, wifi) ka theme control karta hai (`light-content` vs `dark-content`).
3. **`KeyboardAvoidingView`:** Jab software keyboard open hota hai, to form inputs keyboard ke peeche na dabein, screen ko automatically shift karta hai.

```tsx
import React from "react";
import {
  KeyboardAvoidingView,
  Platform,
  StatusBar,
  StyleSheet,
  View,
} from "react-native";
import { SafeAreaView, SafeAreaProvider } from "react-native-safe-area-context";

export const ScreenWrapper = ({ children }: { children: React.ReactNode }) => {
  return (
    <SafeAreaProvider>
      <SafeAreaView style={styles.safeArea} edges={["top", "left", "right"]}>
        <StatusBar barStyle="light-content" backgroundColor="#0B0F19" />
        <KeyboardAvoidingView
          behavior={Platform.OS === "ios" ? "padding" : "height"}
          style={styles.keyboardContainer}
          keyboardVerticalOffset={Platform.OS === "ios" ? 64 : 0}
        >
          <View style={styles.content}>{children}</View>
        </KeyboardAvoidingView>
      </SafeAreaView>
    </SafeAreaProvider>
  );
};

const styles = StyleSheet.create({
  safeArea: {
    flex: 1,
    backgroundColor: "#0B0F19",
  },
  keyboardContainer: {
    flex: 1,
  },
  content: {
    flex: 1,
    padding: 16,
  },
});
```

<br>
<br>

## 🐦‍🔥 LAYOUT & STYLING (YOGA LAYOUT ENGINE)

React Native layouting ke liye **Yoga** engine use karta hai jo C++ me likha gaya open-source layout engine hai. Ye W3C Flexbox specifications ko native platforms par calculate karta hai.

### 🔥 Flexbox: React Native vs Web Differences

⚡ **Crucial Differences:**

1. **Default Direction:** Web par `flexDirection` default `row` hoti hai. React Native me screen vertically scroll hoti hai, isliye default `flexDirection: 'column'` hoti hai.
2. **`flex: 1` Mental Model:** Web par `flex: 1` shorthand hota hai `flex: 1 1 0%`. React Native me `flex: 1` ka seedha matlab hai: "Available parent space ko proportionally occupy kar lo".
3. **No CSS Cascade:** Style inheritence sirf `<Text>` components ke nesting me limited hoti hai. Container `<View>` ka font color child `<Text>` me auto-inherit nahi hota.

```text
flexDirection: 'column' (Default)           flexDirection: 'row'
     +-------------------+                     +-------------------+
     |   Child 1         |                     | Child1 | Child2   |
     +-------------------+                     |        |          |
     |   Child 2         |                     +-------------------+
     +-------------------+                     Main Axis: Horizontal (X)
     Main Axis: Vertical (Y)                   Cross Axis: Vertical (Y)
     Cross Axis: Horizontal (X)
```

⚡ **Axis Alignment Reference:**

- `justifyContent`: Main Axis ke along items ko align karta hai (`flex-start`, `center`, `flex-end`, `space-between`, `space-around`, `space-evenly`).
- `alignItems`: Cross Axis ke along items ko align karta hai (`flex-start`, `center`, `flex-end`, `stretch`).

<br>

### 🔥 StyleSheet API & Performance Optimization

Kabhi bhi dynamic styling ke alawa inline objects style prop me directly mat pass karein jaise `<View style={{ margin: 10 }}>`.

⚡ **Kyun? (The Engineering Reason):**

- Inline object dene se har re-render par naya memory reference allocate hota hai, jisse Garbage Collector trigger hota hai aur child components ka shallow prop comparison fail ho jata hai.
- `StyleSheet.create()` styles ko integer IDs me map karta hai aur C++ Yoga layer me bridge ke across ek hi baar push karta hai. Isse serialization cost zero ho jati hai.

```tsx
import React from "react";
import { View, Text, StyleSheet } from "react-native";

export const OptimizedCard = () => {
  return (
    <View style={styles.card}>
      <Text style={styles.title}>Performance First</Text>
    </View>
  );
};

const styles = StyleSheet.create({
  card: {
    backgroundColor: "#1E293B",
    padding: 20,
    borderRadius: 16,
    // Elevation for Android
    elevation: 4,
    // Shadows for iOS
    shadowColor: "#000000",
    shadowOffset: { width: 0, height: 4 },
    shadowOpacity: 0.3,
    shadowRadius: 8,
  },
  title: {
    color: "#F8FAFC",
    fontSize: 18,
    fontWeight: "700",
  },
});
```

<br>

### 🔥 Responsive Layouts: Dimensions vs useWindowDimensions

- `Dimensions.get('window')`: Static snapshot return karta hai. Agar user phone rotate karta hai (Portrait to Landscape) ya Foldable phone unfold hota hai, to `Dimensions` update nahi hota jab tak event listener na lagaya ho.
- `useWindowDimensions()`: React hook hai jo dimension change hone par automatically re-render trigger karta hai aur accurate screen height/width deliver karta hai.

```tsx
import React from "react";
import { View, Text, StyleSheet, useWindowDimensions } from "react-native";

export const ResponsiveGrid = () => {
  const { width, height } = useWindowDimensions();
  const isTablet = width >= 768;

  return (
    <View style={[styles.container, isTablet && styles.tabletContainer]}>
      <Text style={styles.infoText}>
        Viewport: {Math.round(width)} x {Math.round(height)} |{" "}
        {isTablet ? "Tablet" : "Phone"}
      </Text>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 16,
    backgroundColor: "#0F172A",
  },
  tabletContainer: {
    paddingHorizontal: 64,
  },
  infoText: {
    color: "#38BDF8",
    fontSize: 16,
  },
});
```

<br>

### 🔥 Integrating NativeWind (Tailwind CSS for React Native)

NativeWind Tailwind CSS ke utility classes ko compile-time par native `StyleSheet` objects me transform karta hai.

⚡ **Step 1: Install Dependencies**

```bash
npm install nativewind
npm install --save-dev tailwindcss@3.3.2
```

⚡ **Step 2: Initialize Tailwind Config**

```bash
npx tailwindcss init
```

⚡ **Step 3: Configure `tailwind.config.js`**

```js
/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./App.{js,jsx,ts,tsx}", "./src/**/*.{js,jsx,ts,tsx}"],
  theme: {
    extend: {
      colors: {
        brand: "#6366F1",
      },
    },
  },
  plugins: [],
};
```

⚡ **Step 4: Update `babel.config.js`**

```js
module.exports = {
  presets: ["module:@react-native/babel-preset"],
  plugins: ["nativewind/babel"],
};
```

⚡ **Step 5: Usage with TypeScript declarations (`app.d.ts`)**

```ts
/// <reference types="nativewind/types" />
```

```tsx
import { View, Text } from "react-native";

export const TailwindCard = () => {
  return (
    <View className="bg-slate-900 p-6 rounded-2xl border border-slate-800 shadow-lg">
      <Text className="text-indigo-400 font-bold text-xl">
        NativeWind Active
      </Text>
      <Text className="text-slate-400 mt-2 text-sm">
        Styled using familiar utility classes compiled to native Yoga nodes.
      </Text>
    </View>
  );
};
```

<br>
<br>

## 🐦‍🔥 SCROLLABLE VIEWS & PERFORMANCE

Mobile apps me scrolling performance sabse critical metric hota hai. Wrong list component choose karne se out-of-memory (OOM) crashes aur 10 FPS jank dekhne ko milta hai.

### 🔥 `<ScrollView>` vs `<FlatList>` vs `<SectionList>`

| Component           | Virtualization                                                          | Memory Usage                                                        | Best For                                                  |
| :------------------ | :---------------------------------------------------------------------- | :------------------------------------------------------------------ | :-------------------------------------------------------- |
| **`<ScrollView>`**  | No. Har child item ek hi bar me memory me allocate hota hai.            | High (proportional to total data).                                  | Static forms, settings pages, short content (< 30 items). |
| **`<FlatList>`**    | Yes. Sirf screen par visible items render hote hain (Recycler pattern). | Low & Constant. Screen se bahar gaye elements unmount ho jate hain. | Long feeds, infinite scroll, e-commerce product catalogs. |
| **`<SectionList>`** | Yes. FlatList jaisi virtualization plus sticky section headers.         | Low & Constant.                                                     | Alphabetical contacts, categorized menus, grouped logs.   |

⚡ **Hinglish Analogy (Hotel Buffet vs Unlimited Menu on Demand):**

- **ScrollView:** Maan lo 10,000 guests ke aane se pehle hi kitchen me 10,000 thaliyan table par saja ke rakh di. Hotel ka space (RAM) turant full ho jayega aur system crash ho jayega.
- **FlatList (Virtualization):** Kitchen sirf un 5 guests ke liye thali banata hai jo abhi table par baithe hain. Jaise hi koi uth ke gaya, wahi plate wash karke agle aane wale guest ko serve kar di jati hai.

<br>

### 🔥 Deep Dive: Optimized `<FlatList>` Implementation

```tsx
import React, { useState, useCallback } from "react";
import {
  FlatList,
  View,
  Text,
  StyleSheet,
  ListRenderItem,
  RefreshControl,
  ActivityIndicator,
} from "react-native";

interface Transaction {
  id: string;
  title: string;
  amount: string;
  timestamp: string;
}

const ITEM_HEIGHT = 72; // Fixed height enables getItemLayout optimization

export const TransactionList = () => {
  const [data, setData] = useState<Transaction[]>([
    {
      id: "1",
      title: "Server Hosting",
      amount: "-$120.00",
      timestamp: "10:30 AM",
    },
    {
      id: "2",
      title: "Client Payment",
      amount: "+$2,400.00",
      timestamp: "Yesterday",
    },
    {
      id: "3",
      title: "Domain Renewal",
      amount: "-$14.99",
      timestamp: "Oct 18",
    },
  ]);
  const [refreshing, setRefreshing] = useState(false);

  const onRefresh = useCallback(async () => {
    setRefreshing(true);
    // Simulate network delay
    await new Promise((resolve) => setTimeout(resolve, 1500));
    setRefreshing(false);
  }, []);

  const renderItem: ListRenderItem<Transaction> = useCallback(
    ({ item }) => (
      <View style={styles.itemRow}>
        <View>
          <Text style={styles.itemTitle}>{item.title}</Text>
          <Text style={styles.itemSubtitle}>{item.timestamp}</Text>
        </View>
        <Text
          style={[
            styles.amount,
            item.amount.startsWith("+") ? styles.positive : styles.negative,
          ]}
        >
          {item.amount}
        </Text>
      </View>
    ),
    [],
  );

  const keyExtractor = useCallback((item: Transaction) => item.id, []);

  // getItemLayout skips dynamic measurement calculations for layout engine
  const getItemLayout = useCallback(
    (_: any, index: number) => ({
      length: ITEM_HEIGHT,
      offset: ITEM_HEIGHT * index,
      index,
    }),
    [],
  );

  return (
    <FlatList
      data={data}
      renderItem={renderItem}
      keyExtractor={keyExtractor}
      getItemLayout={getItemLayout}
      // Virtualization Optimization Tuning
      initialNumToRender={10} // Screen load hone par pehle kitne items render ho
      maxToRenderPerBatch={5} // Per scroll batch me kitne items render ho
      windowSize={5} // Render window buffer multiplier (5 = 2 screens above, 1 visible, 2 below)
      removeClippedSubviews={true} // Native view hierarchy se invisible views detach karna
      // UI Enhancements
      ListHeaderComponent={
        <Text style={styles.headerTitle}>Recent Activity</Text>
      }
      ListEmptyComponent={
        <View style={styles.emptyContainer}>
          <Text style={styles.emptyText}>No transactions found.</Text>
        </View>
      }
      refreshControl={
        <RefreshControl
          refreshing={refreshing}
          onRefresh={onRefresh}
          tintColor="#6366F1"
          colors={["#6366F1"]}
        />
      }
      contentContainerStyle={styles.listContent}
    />
  );
};

const styles = StyleSheet.create({
  listContent: {
    padding: 16,
    backgroundColor: "#090D16",
    flexGrow: 1,
  },
  headerTitle: {
    fontSize: 22,
    fontWeight: "800",
    color: "#F8FAFC",
    marginBottom: 16,
  },
  itemRow: {
    height: ITEM_HEIGHT,
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
    backgroundColor: "#131B2E",
    marginBottom: 8,
    paddingHorizontal: 16,
    borderRadius: 12,
  },
  itemTitle: {
    fontSize: 16,
    fontWeight: "600",
    color: "#E2E8F0",
  },
  itemSubtitle: {
    fontSize: 13,
    color: "#64748B",
    marginTop: 2,
  },
  amount: {
    fontSize: 16,
    fontWeight: "700",
  },
  positive: {
    color: "#10B981",
  },
  negative: {
    color: "#EF4444",
  },
  emptyContainer: {
    padding: 40,
    alignItems: "center",
  },
  emptyText: {
    color: "#64748B",
  },
});
```

<br>
<br>

## 🐦‍🔥 NAVIGATION (REACT NAVIGATION V6/V7)

Mobile apps me navigation web ke URL navigation se bilkul different hoti hai. Yahan **Screen Stacks** hote hain jahan ek screen ke upar doosri screen slide hoke baithti hai (Push & Pop stack memory).

### 🔥 Native Dependencies Setup

```bash
# Core Navigation Container
npm install @react-navigation/native

# Platform Native Optimization Dependencies
npm install react-native-screens react-native-safe-area-context

# Stack Navigator
npm install @react-navigation/native-stack

# Bottom Tabs Navigator
npm install @react-navigation/bottom-tabs
```

<br>

### 🔥 Stack Navigation with Type-Safe Route Params

TypeScript ke sath type-safe navigation stack create karna production apps me runtime navigation crashes prevent karta hai.

```tsx
import React from "react";
import { View, Text, Pressable, StyleSheet } from "react-native";
import { NavigationContainer } from "@react-navigation/native";
import {
  createNativeStackNavigator,
  NativeStackScreenProps,
} from "@react-navigation/native-stack";

// 1. Define Route Param List Types
export type RootStackParamList = {
  Home: undefined;
  Details: { productId: string; title: string };
};

// 2. Screen Props Helper Types
type HomeScreenProps = NativeStackScreenProps<RootStackParamList, "Home">;
type DetailsScreenProps = NativeStackScreenProps<RootStackParamList, "Details">;

const Stack = createNativeStackNavigator<RootStackParamList>();

// 3. Screen Components
const HomeScreen = ({ navigation }: HomeScreenProps) => {
  return (
    <View style={styles.centerContainer}>
      <Text style={styles.screenText}>Home Dashboard</Text>
      <Pressable
        style={styles.navButton}
        onPress={() =>
          navigation.navigate("Details", {
            productId: "PROD_9981",
            title: "Mechanical Keyboard Pro",
          })
        }
      >
        <Text style={styles.buttonText}>View Product Details</Text>
      </Pressable>
    </View>
  );
};

const DetailsScreen = ({ route, navigation }: DetailsScreenProps) => {
  const { productId, title } = route.params;

  return (
    <View style={styles.centerContainer}>
      <Text style={styles.titleText}>{title}</Text>
      <Text style={styles.subText}>SKU: {productId}</Text>
      <Pressable style={styles.backButton} onPress={() => navigation.goBack()}>
        <Text style={styles.buttonText}>Go Back</Text>
      </Pressable>
    </View>
  );
};

// 4. Main Stack Shell
export const AppNavigator = () => {
  return (
    <NavigationContainer>
      <Stack.Navigator
        initialRouteName="Home"
        screenOptions={{
          headerStyle: { backgroundColor: "#0F172A" },
          headerTintColor: "#38BDF8",
          headerTitleStyle: { fontWeight: "700" },
          contentStyle: { backgroundColor: "#020617" },
          animation: "slide_from_right",
        }}
      >
        <Stack.Screen
          name="Home"
          component={HomeScreen}
          options={{ title: "Explore" }}
        />
        <Stack.Screen
          name="Details"
          component={DetailsScreen}
          options={({ route }) => ({ title: route.params.title })}
        />
      </Stack.Navigator>
    </NavigationContainer>
  );
};

const styles = StyleSheet.create({
  centerContainer: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    padding: 20,
  },
  screenText: {
    fontSize: 20,
    color: "#F8FAFC",
    marginBottom: 20,
  },
  titleText: {
    fontSize: 22,
    fontWeight: "800",
    color: "#38BDF8",
  },
  subText: {
    fontSize: 14,
    color: "#94A3B8",
    marginVertical: 10,
  },
  navButton: {
    backgroundColor: "#6366F1",
    paddingVertical: 12,
    paddingHorizontal: 20,
    borderRadius: 8,
  },
  backButton: {
    backgroundColor: "#334155",
    paddingVertical: 10,
    paddingHorizontal: 18,
    borderRadius: 8,
    marginTop: 20,
  },
  buttonText: {
    color: "#FFFFFF",
    fontWeight: "600",
  },
});
```

<br>

### 🔥 Bottom Tab Navigation

```tsx
import React from "react";
import { createBottomTabNavigator } from "@react-navigation/bottom-tabs";
import { Text, View, StyleSheet } from "react-native";

const Tab = createBottomTabNavigator();

const FeedScreen = () => (
  <View style={styles.tabContent}>
    <Text style={styles.tabText}>Activity Feed</Text>
  </View>
);
const ProfileScreen = () => (
  <View style={styles.tabContent}>
    <Text style={styles.tabText}>User Profile</Text>
  </View>
);

export const BottomTabNavigator = () => {
  return (
    <Tab.Navigator
      screenOptions={{
        headerShown: false,
        tabBarStyle: {
          backgroundColor: "#0F172A",
          borderTopColor: "#1E293B",
          height: 60,
          paddingBottom: 8,
        },
        tabBarActiveTintColor: "#6366F1",
        tabBarInactiveTintColor: "#64748B",
      }}
    >
      <Tab.Screen name="Feed" component={FeedScreen} />
      <Tab.Screen name="Profile" component={ProfileScreen} />
    </Tab.Navigator>
  );
};

const styles = StyleSheet.create({
  tabContent: {
    flex: 1,
    backgroundColor: "#020617",
    justifyContent: "center",
    alignItems: "center",
  },
  tabText: {
    color: "#F8FAFC",
    fontSize: 18,
  },
});
```

<br>

### 🔥 Nested Navigation Architecture (Auth Flow vs App Flow)

Production apps me user agar authenticated nahi hai to use Login/Register stack dikhaya jata hai; authenticate hone ke baad direct Main Tab Dashboard par switch kar diya jata hai bina back button se login screen par wapas jane diye.

```text
RootNavigator (Conditional Auth Switch)
  ├── (userToken == null) ➔ AuthStack (Login, Register, ForgotPassword)
  └── (userToken != null) ➔ MainAppTabNavigator
                               ├── FeedStack
                               ├── SearchScreen
                               └── ProfileStack
```

<br>
<br>

## 🐦‍🔥 STATE MANAGEMENT & DATA FETCHING

Mobile apps me network bandwidth flaky hoti hai (user elevator me ho sakta hai ya train me signal drop ho sakta hai). Isliye state management aur data persistence bohot strong hona chahiye.

### 🔥 Global State: Zustand Setup for Mobile

Redux Toolkit ke mukable **Zustand** React Native me lightweight aur fast hai. Isme zero boilerplate hota hai aur selective selector updates ki wajah se unwanted parent-to-child re-render traps avoid ho jate hain.

```bash
npm install zustand
```

```tsx
import { create } from "zustand";

interface UserProfile {
  id: string;
  name: string;
  email: string;
}

interface AuthState {
  user: UserProfile | null;
  isAuthenticated: boolean;
  setUser: (user: UserProfile) => void;
  logout: () => void;
}

export const useAuthStore = create<AuthState>((set) => ({
  user: null,
  isAuthenticated: false,
  setUser: (user) => set({ user, isAuthenticated: true }),
  logout: () => set({ user: null, isAuthenticated: false }),
}));

// Component Usage with Selector:
// const user = useAuthStore((state) => state.user);
// const logout = useAuthStore((state) => state.logout);
```

<br>

### 🔥 Axios API Client with Persistent Token Storage

```bash
npm install axios @react-native-async-storage/async-storage
```

```tsx
import axios from "axios";
import AsyncStorage from "@react-native-async-storage/async-storage";

const API_BASE_URL = "https://api.example.com/v1";

export const apiClient = axios.create({
  baseURL: API_BASE_URL,
  timeout: 10000,
  headers: {
    "Content-Type": "application/json",
  },
});

// Request Interceptor: Injects Bearer token from local device storage
apiClient.interceptors.request.use(
  async (config) => {
    try {
      const token = await AsyncStorage.getItem("@auth_jwt_token");
      if (token && config.headers) {
        config.headers.Authorization = `Bearer ${token}`;
      }
    } catch (storageError) {
      console.warn("Storage read failed", storageError);
    }
    return config;
  },
  (error) => Promise.reject(error),
);

// Response Interceptor: Catches 401 Unauthorized globally
apiClient.interceptors.response.use(
  (response) => response,
  async (error) => {
    if (error.response?.status === 401) {
      // Clear token and trigger auth logout action
      await AsyncStorage.removeItem("@auth_jwt_token");
    }
    return Promise.reject(error);
  },
);
```

<br>
<br>

## 🐦‍🔥 NATIVE DEVICE APIS & PERMISSIONS

### 🔥 Runtime Android & iOS Permissions

Modern operating systems me user se runtime par permission maangna zaroori hota hai jab feature actually demand ho.

```tsx
import { Platform, PermissionsAndroid, Alert } from "react-native";

export const requestCameraPermission = async (): Promise<boolean> => {
  if (Platform.OS === "android") {
    try {
      const granted = await PermissionsAndroid.request(
        PermissionsAndroid.PERMISSIONS.CAMERA,
        {
          title: "Camera Access Needed",
          message: "This application requires camera access to scan invoices.",
          buttonNeutral: "Ask Me Later",
          buttonNegative: "Cancel",
          buttonPositive: "Allow",
        },
      );
      return granted === PermissionsAndroid.RESULTS.GRANTED;
    } catch (err) {
      console.warn("Permission error", err);
      return false;
    }
  }
  // iOS permissions are automatically declared in Info.plist (NSCameraUsageDescription)
  return true;
};
```

<br>

### 🔥 Local Key-Value Storage: AsyncStorage Wrapper Hook

`AsyncStorage` mobile devices ke native key-value storage (Android SQLite/SharedPrefs, iOS CoreData/Files) ko asynchronous promise-based API ke sath expose karta hai.

```tsx
import { useState, useEffect, useCallback } from "react";
import AsyncStorage from "@react-native-async-storage/async-storage";

export function useStoredState<T>(
  key: string,
  initialValue: T,
): [T, (value: T) => Promise<void>, boolean] {
  const [storedValue, setStoredValue] = useState<T>(initialValue);
  const [loading, setLoading] = useState<boolean>(true);

  useEffect(() => {
    const loadValue = async () => {
      try {
        const item = await AsyncStorage.getItem(key);
        if (item !== null) {
          setStoredValue(JSON.parse(item));
        }
      } catch (e) {
        console.error(`Failed to load key: ${key}`, e);
      } finally {
        setLoading(false);
      }
    };
    loadValue();
  }, [key]);

  const updateValue = useCallback(
    async (value: T) => {
      try {
        setStoredValue(value);
        await AsyncStorage.setItem(key, JSON.stringify(value));
      } catch (e) {
        console.error(`Failed to save key: ${key}`, e);
      }
    },
    [key],
  );

  return [storedValue, updateValue, loading];
}
```

<br>

### 🔥 Device Hardware: Camera & Gallery Access

Media picker implement karne ke liye `react-native-image-picker` production standard package hai.

```bash
npm install react-native-image-picker
```

```tsx
import React, { useState } from "react";
import { View, Image, StyleSheet, Text, Pressable } from "react-native";
import {
  launchCamera,
  launchImageLibrary,
  ImagePickerResponse,
} from "react-native-image-picker";

export const MediaUploadModule = () => {
  const [selectedUri, setSelectedUri] = useState<string | null>(null);

  const handleCameraCapture = async () => {
    const result: ImagePickerResponse = await launchCamera({
      mediaType: "photo",
      cameraType: "back",
      quality: 0.8,
      saveToPhotos: true,
    });

    if (result.assets && result.assets.length > 0) {
      setSelectedUri(result.assets[0].uri ?? null);
    }
  };

  const handleGallerySelection = async () => {
    const result: ImagePickerResponse = await launchImageLibrary({
      mediaType: "photo",
      selectionLimit: 1,
      quality: 0.8,
    });

    if (result.assets && result.assets.length > 0) {
      setSelectedUri(result.assets[0].uri ?? null);
    }
  };

  return (
    <View style={styles.mediaContainer}>
      {selectedUri ? (
        <Image source={{ uri: selectedUri }} style={styles.preview} />
      ) : (
        <View style={styles.placeholder}>
          <Text style={styles.placeholderText}>No image selected</Text>
        </View>
      )}

      <View style={styles.buttonRow}>
        <Pressable style={styles.actionBtn} onPress={handleCameraCapture}>
          <Text style={styles.btnText}>Open Camera</Text>
        </Pressable>
        <Pressable
          style={[styles.actionBtn, styles.galleryBtn]}
          onPress={handleGallerySelection}
        >
          <Text style={styles.btnText}>Open Gallery</Text>
        </Pressable>
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  mediaContainer: {
    backgroundColor: "#1E293B",
    padding: 16,
    borderRadius: 16,
    alignItems: "center",
    marginVertical: 12,
  },
  preview: {
    width: 220,
    height: 220,
    borderRadius: 12,
    marginBottom: 16,
  },
  placeholder: {
    width: 220,
    height: 220,
    borderRadius: 12,
    backgroundColor: "#0F172A",
    justifyContent: "center",
    alignItems: "center",
    marginBottom: 16,
    borderWidth: 1,
    borderColor: "#334155",
    borderStyle: "dashed",
  },
  placeholderText: {
    color: "#64748B",
    fontSize: 14,
  },
  buttonRow: {
    flexDirection: "row",
    gap: 12,
  },
  actionBtn: {
    backgroundColor: "#6366F1",
    paddingVertical: 10,
    paddingHorizontal: 16,
    borderRadius: 8,
  },
  galleryBtn: {
    backgroundColor: "#0284C7",
  },
  btnText: {
    color: "#FFFFFF",
    fontWeight: "600",
    fontSize: 14,
  },
});
```

<br>

### 🔥 Device Hardware: GPS & Real-Time Location Tracking

Production location tracking ke liye battery-efficient high-accuracy geolocation service:

```bash
npm install react-native-geolocation-service
```

```tsx
import React, { useState, useEffect } from "react";
import {
  View,
  Text,
  StyleSheet,
  Platform,
  PermissionsAndroid,
} from "react-native";
import Geolocation from "react-native-geolocation-service";

interface Coordinates {
  latitude: number;
  longitude: number;
  accuracy: number;
}

export const LocationTracker = () => {
  const [coords, setCoords] = useState<Coordinates | null>(null);
  const [errorMsg, setErrorMsg] = useState<string | null>(null);

  useEffect(() => {
    let watchId: number | null = null;

    const startTracking = async () => {
      let hasPermission = false;

      if (Platform.OS === "android") {
        const granted = await PermissionsAndroid.request(
          PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
        );
        hasPermission = granted === PermissionsAndroid.RESULTS.GRANTED;
      } else {
        const auth = await Geolocation.requestAuthorization("whenInUse");
        hasPermission = auth === "granted";
      }

      if (!hasPermission) {
        setErrorMsg("Location permission denied");
        return;
      }

      // Continuous high-precision GPS watcher
      watchId = Geolocation.watchPosition(
        (position) => {
          setCoords({
            latitude: position.coords.latitude,
            longitude: position.coords.longitude,
            accuracy: position.coords.accuracy,
          });
        },
        (error) => {
          setErrorMsg(error.message);
        },
        {
          enableHighAccuracy: true,
          distanceFilter: 10, // Har 10 meters distance move hone par update
          interval: 5000,
          fastestInterval: 2000,
        },
      );
    };

    startTracking();

    return () => {
      if (watchId !== null) {
        Geolocation.clearWatch(watchId);
      }
    };
  }, []);

  return (
    <View style={styles.geoBox}>
      <Text style={styles.geoTitle}>⚡ GPS Telemetry</Text>
      {errorMsg ? (
        <Text style={styles.errorText}>{errorMsg}</Text>
      ) : coords ? (
        <View style={styles.coordBox}>
          <Text style={styles.coordText}>
            Lat: {coords.latitude.toFixed(5)}
          </Text>
          <Text style={styles.coordText}>
            Long: {coords.longitude.toFixed(5)}
          </Text>
          <Text style={styles.accuracyText}>
            Accuracy: ±{Math.round(coords.accuracy)}m
          </Text>
        </View>
      ) : (
        <Text style={styles.loadingText}>Acquiring GPS Satellite Lock...</Text>
      )}
    </View>
  );
};

const styles = StyleSheet.create({
  geoBox: {
    backgroundColor: "#0F172A",
    padding: 16,
    borderRadius: 12,
    borderWidth: 1,
    borderColor: "#1E293B",
    marginVertical: 10,
  },
  geoTitle: {
    color: "#38BDF8",
    fontWeight: "700",
    fontSize: 16,
    marginBottom: 8,
  },
  coordBox: {
    gap: 4,
  },
  coordText: {
    color: "#F8FAFC",
    fontSize: 14,
    fontFamily: Platform.OS === "ios" ? "Menlo" : "monospace",
  },
  accuracyText: {
    color: "#10B981",
    fontSize: 12,
    marginTop: 4,
  },
  errorText: {
    color: "#EF4444",
  },
  loadingText: {
    color: "#94A3B8",
  },
});
```

<br>
<br>

## 🐦‍🔥 ANIMATIONS (REANIMATED 3 & GESTURE HANDLER)

Purana `Animated` API bridge ke across value updates serialise karta tha. Agar JS thread kisi calculation me busy ho gaya, to animation freeze ho jati thi.
**React Native Reanimated 3** animations ko directly **UI Thread** par 60-120 FPS par execute karta hai via C++ worklets.

### 🔥 Setup

```bash
npm install react-native-reanimated react-native-gesture-handler
```

`babel.config.js` me plugin add karein:

```js
module.exports = {
  plugins: [
    "react-native-reanimated/plugin", // MUST BE LISTED LAST
  ],
};
```

<br>

### 🔥 Declarative Animation: Fade & Spring Card

```tsx
import React from "react";
import { View, StyleSheet, Pressable, Text } from "react-native";
import Animated, {
  useSharedValue,
  useAnimatedStyle,
  withSpring,
  withTiming,
} from "react-native-reanimated";

export const InteractiveAnimatedCard = () => {
  // Shared value lives on the UI thread
  const scale = useSharedValue(1);
  const opacity = useSharedValue(0.8);

  const animatedStyle = useAnimatedStyle(() => {
    return {
      transform: [{ scale: scale.value }],
      opacity: opacity.value,
    };
  });

  const handlePressIn = () => {
    scale.value = withSpring(0.95);
    opacity.value = withTiming(1, { duration: 150 });
  };

  const handlePressOut = () => {
    scale.value = withSpring(1, { damping: 12, stiffness: 100 });
    opacity.value = withTiming(0.8, { duration: 150 });
  };

  return (
    <View style={styles.wrapper}>
      <Pressable onPressIn={handlePressIn} onPressOut={handlePressOut}>
        <Animated.View style={[styles.card, animatedStyle]}>
          <Text style={styles.cardText}>Interactive Spring Physics</Text>
        </Animated.View>
      </Pressable>
    </View>
  );
};

const styles = StyleSheet.create({
  wrapper: {
    padding: 24,
    alignItems: "center",
  },
  card: {
    width: 280,
    height: 140,
    backgroundColor: "#4F46E5",
    borderRadius: 20,
    justifyContent: "center",
    alignItems: "center",
  },
  cardText: {
    color: "#FFFFFF",
    fontWeight: "700",
    fontSize: 16,
  },
});
```

<br>

### 🔥 Pan Gestures: Drag-to-Dismiss / Pan Gesture Handler

```tsx
import React from "react";
import { StyleSheet, View } from "react-native";
import {
  GestureDetector,
  Gesture,
  GestureHandlerRootView,
} from "react-native-gesture-handler";
import Animated, {
  useSharedValue,
  useAnimatedStyle,
  withSpring,
} from "react-native-reanimated";

export const DraggableWidget = () => {
  const translationX = useSharedValue(0);
  const translationY = useSharedValue(0);
  const prevTranslationX = useSharedValue(0);
  const prevTranslationY = useSharedValue(0);

  const panGesture = Gesture.Pan()
    .onStart(() => {
      prevTranslationX.value = translationX.value;
      prevTranslationY.value = translationY.value;
    })
    .onUpdate((event) => {
      translationX.value = prevTranslationX.value + event.translationX;
      translationY.value = prevTranslationY.value + event.translationY;
    })
    .onEnd(() => {
      // Spring back to origin on release
      translationX.value = withSpring(0);
      translationY.value = withSpring(0);
    });

  const animatedStyle = useAnimatedStyle(() => ({
    transform: [
      { translateX: translationX.value },
      { translateY: translationY.value },
    ],
  }));

  return (
    <GestureHandlerRootView style={styles.flexOne}>
      <View style={styles.container}>
        <GestureDetector gesture={panGesture}>
          <Animated.View style={[styles.box, animatedStyle]} />
        </GestureDetector>
      </View>
    </GestureHandlerRootView>
  );
};

const styles = StyleSheet.create({
  flexOne: { flex: 1 },
  container: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#090D16",
  },
  box: {
    width: 100,
    height: 100,
    backgroundColor: "#06B6D4",
    borderRadius: 24,
  },
});
```

<br>

### 🔥 Pinch Gestures: Pinch-to-Zoom

```tsx
import React from "react";
import { StyleSheet, View } from "react-native";
import {
  GestureDetector,
  Gesture,
  GestureHandlerRootView,
} from "react-native-gesture-handler";
import Animated, {
  useSharedValue,
  useAnimatedStyle,
  withTiming,
} from "react-native-reanimated";

export const PinchableImage = () => {
  const scale = useSharedValue(1);
  const savedScale = useSharedValue(1);

  const pinchGesture = Gesture.Pinch()
    .onUpdate((e) => {
      scale.value = savedScale.value * e.scale;
    })
    .onEnd(() => {
      if (scale.value < 1) {
        scale.value = withTiming(1);
        savedScale.value = 1;
      } else {
        savedScale.value = scale.value;
      }
    });

  const animatedStyle = useAnimatedStyle(() => ({
    transform: [{ scale: scale.value }],
  }));

  return (
    <GestureHandlerRootView style={styles.flexOne}>
      <View style={styles.container}>
        <GestureDetector gesture={pinchGesture}>
          <Animated.Image
            source={{
              uri: "https://images.unsplash.com/photo-1579783902614-a3fb3927b675?w=600",
            }}
            style={[styles.image, animatedStyle]}
            resizeMode="cover"
          />
        </GestureDetector>
      </View>
    </GestureHandlerRootView>
  );
};

const styles = StyleSheet.create({
  flexOne: { flex: 1 },
  container: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#090D16",
  },
  image: {
    width: 280,
    height: 280,
    borderRadius: 16,
  },
});
```

<br>
<br>

## 🐦‍🔥 NATIVE MODULES & BRIDGING (ADVANCED)

Jab koi npm package exist nahi karta ya aapko hardware SDK (e.g. thermal printer, custom biometric scanner) integrate karni hoti hai, tab custom Native Modules likhe jaate hain.

### 🔥 Writing a Custom Android Native Module (Kotlin)

⚡ **Step 1: Create the Native Module (`DeviceBatteryModule.kt`)**

```kotlin
package com.mycliapp

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod
import com.facebook.react.bridge.Promise
import android.os.BatteryManager
import android.content.Context

class DeviceBatteryModule(reactContext: ReactApplicationContext) : ReactContextBaseJavaModule(reactContext) {
    override fun getName(): String {
        return "DeviceBattery"
    }

    @ReactMethod
    fun getBatteryLevel(promise: Promise) {
        try {
            val bm = reactApplicationContext.getSystemService(Context.BATTERY_SERVICE) as BatteryManager
            val batLevel = bm.getIntProperty(BatteryManager.BATTERY_PROPERTY_CAPACITY)
            promise.resolve(batLevel)
        } catch (e: Exception) {
            promise.reject("ERR_BATTERY", "Could not fetch battery level", e)
        }
    }
}
```

⚡ **Step 2: Register Package (`DeviceBatteryPackage.kt`)**

```kotlin
package com.mycliapp

import com.facebook.react.ReactPackage
import com.facebook.react.bridge.NativeModule
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.uimanager.ViewManager

class DeviceBatteryPackage : ReactPackage {
    override fun createNativeModules(reactContext: ReactApplicationContext): List<NativeModule> {
        return listOf(DeviceBatteryModule(reactContext))
    }

    override fun createViewManagers(reactContext: ReactApplicationContext): List<ViewManager<*, *>> {
        return emptyList()
    }
}
```

⚡ **Step 3: Call from JavaScript / TypeScript**

```tsx
import { NativeModules } from "react-native";

const { DeviceBattery } = NativeModules;

export const fetchBatteryStatus = async (): Promise<number> => {
  try {
    const level: number = await DeviceBattery.getBatteryLevel();
    return level;
  } catch (error) {
    console.error("Failed to get battery", error);
    return -1;
  }
};
```

⚡ **TurboModules (The New Architecture Way):**
TurboModules me manually Java reflection ya JSON serialization use nahi hoti. TypeScript me specification likhi jaati hai (`Spec.ts`), aur codegen tool automatically C++ interfaces generate karta hai. JavaScript engine C++ JSI bindings ke through native methods directly invoke karta hai bina kisi bridge overhead ke.

<br>
<br>

## 🐦‍🔥 PRODUCTION READINESS, TESTING & DEPLOYMENT

### 🔥 Performance Optimization Strategies

⚡ **1. Re-render Prevention:**

- Child components ko `React.memo` se wrap karein jab props frequently change na ho rahe hon.
- Non-primitive functions ko `useCallback` me wrap karein taaki har render par function pointer reference change na ho.
- Heavy filtering/sorting calculations ko `useMemo` me cache karein.

⚡ **2. Image Caching & High Performance:**
React Native standard `<Image>` component aggressive caching support nahi karta. Production me **`react-native-fast-image`** ya **`expo-image`** use karein:

- Memory and disk caching.
- Priority loading (`FastImage.priority.high`).
- Progressive loading placeholders.

⚡ **3. Profile via Flipper & React DevTools:**

- Profiler tab me check karein kaunse components flamegraph me unnecessarily render ho rahe hain.
- Hermes memory tab me leaks trace karein.

<br>

### 🔥 Environment Configuration

Sensitive credentials (API keys, OAuth client IDs) ko directly codebase me hardcode na karein.

```bash
npm install react-native-config
```

⚡ **`.env.production`**

```text
API_URL=https://production.api.domain.com/v1
BUILD_FLAVOR=production
ENABLE_ANALYTICS=true
```

```tsx
import Config from "react-native-config";

console.log("Target API Host:", Config.API_URL);
```

<br>

### 🔥 Android Build & Release Pipeline (APK & AAB)

Google Play Store ab standard APKs accept nahi karta; production deployment ke liye **Android App Bundle (.aab)** mandatory hai.

⚡ **Step 1: Generate Release Keystore**
Run in terminal (PowerShell or Bash):

```bash
keytool -genkeypair -v -storetype PKCS12 -keystore my-release-key.keystore -alias my-key-alias -keyalg RSA -keysize 2048 -validity 10000
```

Move `my-release-key.keystore` to `android/app/` directory.

⚡ **Step 2: Configure `android/gradle.properties`**

```properties
MYAPP_UPLOAD_STORE_FILE=my-release-key.keystore
MYAPP_UPLOAD_KEY_ALIAS=my-key-alias
MYAPP_UPLOAD_STORE_PASSWORD=your_secure_keystore_password
MYAPP_UPLOAD_KEY_PASSWORD=your_secure_key_password
```

⚡ **Step 3: Update `android/app/build.gradle`**

```groovy
android {
    ...
    signingConfigs {
        release {
            if (project.hasProperty('MYAPP_UPLOAD_STORE_FILE')) {
                storeFile file(MYAPP_UPLOAD_STORE_FILE)
                storePassword MYAPP_UPLOAD_STORE_PASSWORD
                keyAlias MYAPP_UPLOAD_KEY_ALIAS
                keyPassword MYAPP_UPLOAD_KEY_PASSWORD
            }
        }
    }
    buildTypes {
        release {
            signingConfig signingConfigs.release
            minifyEnabled true
            shrinkResources true
            proguardFiles getDefaultProguardFile("proguard-android.txt"), "proguard-rules.pro"
        }
    }
}
```

⚡ **Step 4: Build Bundles**

```bash
# Navigate to Android folder
cd android

# Generate Production Android App Bundle (.aab for Google Play Store)
./gradlew bundleRelease

# Generate Universal APK (for direct device installation testing)
./gradlew assembleRelease
```

Artifacts output path: `android/app/build/outputs/bundle/release/app-release.aab`.

<br>

### 🔥 iOS Build & Release Pipeline

⚡ **Prerequisites:** Apple Developer Account ($99/year), macOS machine, Xcode.

1. **Bundle Identifier Setup:** Xcode open karein `ios/MyCliApp.xcworkspace`, aur unique Bundle Identifier set karein (e.g., `com.company.myapp`).
2. **Code Signing:** Xcode -> Project Settings -> _Signing & Capabilities_ -> Automatic signing enable karein aur Apple Developer Team select karein.
3. **Archive Build:**
   - Destination me _Any iOS Device (arm64)_ select karein.
   - Top menu se: _Product ➔ Archive_.
   - Organizer open hoga: _Distribute App ➔ App Store Connect ➔ Upload_.

<br>

### 🔥 Over-The-Air (OTA) Updates

Agar sirf JavaScript bundle ya static images me minor bug fix hai (bina kisi native Java/Swift changes ke), to full App Store review cycle (2-3 days) wait karne ki zarurat nahi hoti.

⚡ **EAS Update (Expo Workflow):**

```bash
# Install EAS CLI
npm install -g eas-cli

# Login and configure
eas login
eas update:configure

# Publish instant patch to production channel
eas update --branch production --message "Fix checkout tax calculation"
```

Jab user next time app open karega, background me latest Hermes JS bundle download hoke seamlessly apply ho jayega.

<br>

---

⚡ **Production Checklist Before Launch:**

- ⚡ Hermes Engine enabled (`hermesEnabled=true`).
- ⚡ Proguard & R8 code shrinking turned on for Android.
- ⚡ Native splash screen configured properly to avoid white flash.
- ⚡ Console logs stripped in production builds via `babel-plugin-transform-remove-console`.
- ⚡ Crash reporting integrated (Sentry / Datadog / Firebase Crashlytics).

</div>
</div>
