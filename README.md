# Portfolio — Paul-Marie Samuel NDZEGHA BOUNGOU

Portfolio web moderne construit avec **Astro** et déployé sur **Vercel**.

🌐 **[portfolio-paul-marie-samuel.vercel.app](https://portfolio-paul-marie-samuel.vercel.app)**

---

## Structure du projet

```
├── src/
│   ├── components/    # Composants Astro réutilisables
│   │   ├── Header.astro
│   │   ├── Hero.astro
│   │   ├── About.astro
│   │   ├── Skills.astro
│   │   ├── Education.astro
│   │   ├── Projects.astro
│   │   ├── Certifications.astro
│   │   ├── Contact.astro
│   │   ├── Footer.astro
│   │   ├── BackToTop.astro
│   │   └── AiAssistant.astro
│   ├── data/
│   │   └── portfolio.ts # Fichier de données centralisé (SEUL fichier à modifier)
│   ├── layouts/
│   │   └── BaseLayout.astro
│   └── pages/
│       └── index.astro
├── public/             # Fichiers statiques (avatar, CV, favicon)
├── astro.config.mjs
├── vercel.json
└── package.json
```

## Commandes

| Commande           | Description                        |
| :----------------- | :--------------------------------- |
| `npm install`      | Installe les dépendances           |
| `npm run dev`      | Serveur de développement           |
| `npm run build`    | Build de production                |
| `npm run preview`  | Prévisualisation du build          |
| `vercel --prod`    | Déploiement en production          |

## Modifier le contenu

Pour mettre à jour le portfolio, modifie **uniquement** le fichier `src/data/portfolio.ts`.
Les sections s'affichent ou se masquent automatiquement selon les données présentes.

## Technologies

- [Astro](https://astro.build) — Framework web statique
- [Vercel](https://vercel.com) — Hébergement & déploiement
- [Lucide Icons](https://lucide.dev) — Icônes SVG
- TypeScript — Typage strict
- CSS Custom Properties — Système de design cohérent

---

Built with ❤️ by Paul-Marie Samuel NDZEGHA BOUNGOU
