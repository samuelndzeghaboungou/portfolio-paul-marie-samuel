/**
 * @fileoverview Centralized data file for the portfolio.
 * This is the ONLY file to edit when updating portfolio content.
 * All sections are conditionally rendered based on the data below.
 */

/* ------------------------------------------------------------------ */
/*  Types                                                              */
/* ------------------------------------------------------------------ */

export interface PersonalInfo {
  firstName: string;
  lastName: string;
  title: string;
  subtitle: string;
  bio: string[];
  emails: string[];
  phone?: string;
  location: string;
  avatar: string;
  availabilityBadge: string;
  cvUrl?: string;
}

export interface Stat {
  label: string;
  value: string;
}

export interface SkillCategory {
  icon: string;
  title: string;
  skills: string[];
}

export interface SoftSkill {
  icon: string;
  name: string;
  description: string;
}

export interface Education {
  period: string;
  degree: string;
  field: string;
  institution: string;
  institutionUrl?: string;
  description: string;
  isLatest?: boolean;
}

export interface Experience {
  period: string;
  role: string;
  company: string;
  companyUrl?: string;
  description: string;
  isCurrent?: boolean;
}

export interface Project {
  title: string;
  description: string;
  tags: string[];
  url?: string;
  github?: string;
}

export interface Certification {
  name: string;
  issuer: string;
  issuerUrl?: string;
  date: string;
  skills: string[];
  icon: string;
}

export interface SocialLink {
  name: string;
  url: string;
  icon: string;
}

export interface NavItem {
  label: string;
  href: string;
  icon: string;
}

/* ------------------------------------------------------------------ */
/*  Personal Information                                               */
/* ------------------------------------------------------------------ */

export const personalInfo: PersonalInfo = {
  firstName: 'Paul-Marie Samuel',
  lastName: 'NDZEGHA BOUNGOU',
  title: 'Étudiant en Ingénierie Logicielle',
  subtitle: 'Passionné par le développement web, mobile & les architectures logicielles modernes',
  bio: [
    "Étudiant en ingénierie logicielle avec une solide formation scientifique (Bac Sciences de la Terre), je me consacre à la conception et au développement de solutions numériques robustes et innovantes. Mon parcours m'a permis de développer une rigueur scientifique que j'applique quotidiennement au code.",
    "Je maîtrise un large éventail de technologies, du front-end au back-end, en passant par les bases de données et le DevOps. Mon objectif : concevoir des applications performantes, maintenables et centrées sur l'utilisateur.",
    "Autodidacte et curieux, je suis constamment en veille technologique. Je m'investis dans des projets personnels et collaboratifs pour renforcer mes compétences et explorer de nouvelles approches de développement.",
    "Actuellement basé à Fès, je suis à la recherche d'un stage en ingénierie logicielle pour mettre en pratique mes connaissances et contribuer à des projets concrets au sein d'une équipe professionnelle."
  ],
  emails: ['s.ndzeghaboungou@esisa.ac.ma'],
  location: 'Fès, Maroc',
  avatar: '/avatar.webp',
  availabilityBadge: 'Disponible pour un stage',
  cvUrl: '/cv-paul-marie-samuel.pdf',
};

/* ------------------------------------------------------------------ */
/*  Key Statistics                                                     */
/* ------------------------------------------------------------------ */

export const stats: Stat[] = [
  { label: 'Projets Réalisés', value: '15+' },
  { label: 'Technologies Maîtrisées', value: '25+' },
  { label: 'Certifications', value: '5+' },
  { label: "Années d'Études Sup.", value: '3+' },
];

/* ------------------------------------------------------------------ */
/*  Technical Skills                                                   */
/* ------------------------------------------------------------------ */

export const technicalSkills: SkillCategory[] = [
  {
    icon: 'code',
    title: 'Langages de Programmation',
    skills: ['JavaScript', 'TypeScript', 'Python', 'Java', 'C', 'C++', 'C#', 'PHP', 'SQL', 'Dart', 'Kotlin', 'HTML5', 'CSS3', 'Bash'],
  },
  {
    icon: 'layout',
    title: 'Front-End',
    skills: ['React', 'Next.js', 'Vue.js', 'Angular', 'Astro', 'Tailwind CSS', 'Bootstrap', 'SASS', 'Redux', 'Vite'],
  },
  {
    icon: 'server',
    title: 'Back-End',
    skills: ['Node.js', 'Express.js', 'NestJS', 'Spring Boot', 'Django', 'Flask', 'Laravel', 'REST API', 'GraphQL'],
  },
  {
    icon: 'database',
    title: 'Bases de Données',
    skills: ['PostgreSQL', 'MySQL', 'MongoDB', 'Redis', 'Firebase', 'SQLite', 'Prisma', 'Sequelize'],
  },
  {
    icon: 'smartphone',
    title: 'Mobile',
    skills: ['React Native', 'Flutter', 'Android (Kotlin)', 'Expo', 'Responsive Design'],
  },
  {
    icon: 'gitBranch',
    title: 'DevOps & Outils',
    skills: ['Git', 'GitHub', 'Docker', 'CI/CD', 'Linux', 'Nginx', 'Vercel', 'Netlify', 'Postman', 'Figma'],
  },
  {
    icon: 'brain',
    title: 'Concepts & Méthodologies',
    skills: ['Agile / Scrum', 'Design Patterns', 'Clean Architecture', 'SOLID', 'TDD', 'UML', 'Merise', 'POO'],
  },
  {
    icon: 'shield',
    title: 'Sécurité & Performance',
    skills: ['JWT', 'OAuth 2.0', 'HTTPS', 'CORS', 'XSS Prevention', 'SQL Injection Prevention', 'Web Performance'],
  },
];

/* ------------------------------------------------------------------ */
/*  Soft Skills                                                        */
/* ------------------------------------------------------------------ */

export const softSkills: SoftSkill[] = [
  { icon: 'users', name: 'Travail d\'équipe', description: 'Capacité à collaborer efficacement dans des projets en groupe et en environnement multiculturel.' },
  { icon: 'lightbulb', name: 'Résolution de problèmes', description: 'Approche analytique et créative pour résoudre les problèmes techniques complexes.' },
  { icon: 'clock', name: 'Gestion du temps', description: 'Organisation efficace pour respecter les délais et prioriser les tâches.' },
  { icon: 'messageCircle', name: 'Communication', description: 'Expression claire des idées techniques et capacité d\'écoute active.' },
  { icon: 'target', name: 'Autonomie', description: 'Capacité à apprendre et travailler de manière indépendante sur des technologies nouvelles.' },
  { icon: 'zap', name: 'Adaptabilité', description: 'Flexibilité face aux changements de technologies et aux nouvelles méthodologies.' },
];

/* ------------------------------------------------------------------ */
/*  Education                                                          */
/* ------------------------------------------------------------------ */

export const education: Education[] = [
  {
    period: '2023 – Présent',
    degree: 'Diplôme d\'Ingénieur',
    field: 'Ingénierie Logicielle',
    institution: 'ESISA – École Supérieure d\'Ingénierie en Sciences Appliquées',
    institutionUrl: 'https://www.esisa.ac.ma',
    description: 'Formation complète en génie logiciel couvrant le développement web & mobile, les architectures logicielles, les bases de données, la cybersécurité, l\'IA et la gestion de projets agiles.',
    isLatest: true,
  },
  {
    period: '2022 – 2023',
    degree: 'Baccalauréat Scientifique',
    field: 'Sciences de la Vie et de la Terre',
    institution: 'Lycée',
    description: 'Obtention du baccalauréat scientifique avec une spécialisation en sciences de la terre, développant une rigueur analytique et une pensée logique.',
  },
];

/* ------------------------------------------------------------------ */
/*  Experience (optional – stages, projets associatifs, freelance)     */
/* ------------------------------------------------------------------ */

export const experience: Experience[] = [];

/* ------------------------------------------------------------------ */
/*  Publications (optional)                                            */
/* ------------------------------------------------------------------ */

export const publications: any[] = [];

/* ------------------------------------------------------------------ */
/*  Projects                                                           */
/* ------------------------------------------------------------------ */

export const projects: Project[] = [
  {
    title: 'Portfolio Personnel',
    description: 'Site web portfolio moderne et responsive construit avec Astro et déployé sur Vercel. Design sombre professionnel avec animations fluides, chatbot IA intégré et performances optimisées.',
    tags: ['Astro', 'TypeScript', 'CSS3', 'Vercel'],
    url: 'https://portfolio-paul-marie-samuel.vercel.app',
    github: 'https://github.com/samuelndzeghaboungou/portfolio-paul-marie-samuel',
  },
  {
    title: 'Application E-Commerce',
    description: 'Plateforme e-commerce complète avec gestion de panier, paiement sécurisé, panel administrateur, et système de recommandations produits. Architecture microservices.',
    tags: ['React', 'Node.js', 'MongoDB', 'Express', 'Redux', 'Stripe'],
    github: 'https://github.com/samuelndzeghaboungou',
  },
  {
    title: 'Application de Gestion de Tâches',
    description: 'Application web collaborative de gestion de tâches avec boards Kanban, drag-and-drop, notifications en temps réel et authentification sécurisée.',
    tags: ['Vue.js', 'NestJS', 'PostgreSQL', 'Socket.io', 'Docker'],
    github: 'https://github.com/samuelndzeghaboungou',
  },
  {
    title: 'Application Mobile Fitness',
    description: 'Application mobile cross-platform pour le suivi d\'entraînements, la planification de séances, le tracking de progression avec graphiques dynamiques et notifications push.',
    tags: ['Flutter', 'Dart', 'Firebase', 'REST API'],
    github: 'https://github.com/samuelndzeghaboungou',
  },
  {
    title: 'API REST Bancaire',
    description: 'API RESTful sécurisée pour la gestion de comptes bancaires avec authentification JWT, transactions, historique et documentation Swagger complète.',
    tags: ['Spring Boot', 'Java', 'PostgreSQL', 'JWT', 'Swagger'],
    github: 'https://github.com/samuelndzeghaboungou',
  },
  {
    title: 'Dashboard Analytics',
    description: 'Tableau de bord interactif pour la visualisation de données en temps réel avec graphiques dynamiques, filtres avancés et export de rapports PDF.',
    tags: ['Next.js', 'TypeScript', 'Chart.js', 'Tailwind CSS', 'Prisma'],
    github: 'https://github.com/samuelndzeghaboungou',
  },
  {
    title: 'Chat en Temps Réel',
    description: 'Application de messagerie instantanée avec salons de discussion, messages privés, partage de fichiers, indicateur de frappe et statut en ligne.',
    tags: ['React', 'Socket.io', 'Node.js', 'MongoDB', 'Redis'],
    github: 'https://github.com/samuelndzeghaboungou',
  },
  {
    title: 'Système de Réservation',
    description: 'Plateforme web de réservation en ligne avec calendrier interactif, gestion des disponibilités, notifications automatiques et paiement intégré.',
    tags: ['Angular', 'Django', 'Python', 'MySQL', 'Docker'],
    github: 'https://github.com/samuelndzeghaboungou',
  },
];

/* ------------------------------------------------------------------ */
/*  Certifications (optional)                                          */
/* ------------------------------------------------------------------ */

export const certifications: Certification[] = [
  {
    name: 'JavaScript Algorithms and Data Structures',
    issuer: 'freeCodeCamp',
    issuerUrl: 'https://www.freecodecamp.org',
    date: '2024',
    skills: ['JavaScript', 'Algorithms', 'Data Structures'],
    icon: 'award',
  },
  {
    name: 'Responsive Web Design',
    issuer: 'freeCodeCamp',
    issuerUrl: 'https://www.freecodecamp.org',
    date: '2024',
    skills: ['HTML5', 'CSS3', 'Responsive Design'],
    icon: 'award',
  },
  {
    name: 'Python for Everybody',
    issuer: 'Coursera – University of Michigan',
    issuerUrl: 'https://www.coursera.org',
    date: '2024',
    skills: ['Python', 'Web Scraping', 'Databases'],
    icon: 'award',
  },
  {
    name: 'Git & GitHub Masterclass',
    issuer: 'Udemy',
    issuerUrl: 'https://www.udemy.com',
    date: '2024',
    skills: ['Git', 'GitHub', 'Version Control'],
    icon: 'award',
  },
  {
    name: 'Introduction to Cybersecurity',
    issuer: 'Cisco Networking Academy',
    issuerUrl: 'https://www.netacad.com',
    date: '2025',
    skills: ['Cybersecurity', 'Network Security', 'Ethical Hacking'],
    icon: 'shield',
  },
];

/* ------------------------------------------------------------------ */
/*  Social Links                                                       */
/* ------------------------------------------------------------------ */

export const socialLinks: SocialLink[] = [
  { name: 'GitHub', url: 'https://github.com/samuelndzeghaboungou', icon: 'github' },
  { name: 'LinkedIn', url: 'https://www.linkedin.com/in/paul-marie-samuel-ndzegha-boungou', icon: 'linkedin' },
  { name: 'Email', url: 'mailto:s.ndzeghaboungou@esisa.ac.ma', icon: 'mail' },
];

/* ------------------------------------------------------------------ */
/*  Dynamic Navigation (auto-generated from active sections)           */
/* ------------------------------------------------------------------ */

function buildNavItems(): NavItem[] {
  const items: NavItem[] = [
    { label: 'Accueil', href: '#hero', icon: 'home' },
    { label: 'À Propos', href: '#about', icon: 'user' },
    { label: 'Compétences', href: '#skills', icon: 'code' },
  ];

  if (education.length > 0) {
    items.push({ label: 'Éducation', href: '#education', icon: 'graduationCap' });
  }
  if (experience.length > 0) {
    items.push({ label: 'Expérience', href: '#experience', icon: 'briefcase' });
  }
  if (publications.length > 0) {
    items.push({ label: 'Publications', href: '#publications', icon: 'fileText' });
  }
  if (projects.length > 0) {
    items.push({ label: 'Projets', href: '#projects', icon: 'folder' });
  }
  if (certifications.length > 0) {
    items.push({ label: 'Certifications', href: '#certifications', icon: 'award' });
  }

  items.push({ label: 'Contact', href: '#contact', icon: 'mail' });

  return items;
}

export const navItems: NavItem[] = buildNavItems();
